//==============================================================================
// Includes
//==============================================================================

#include <cetech/core/container/map.inl>
#include <cetech/core/math/vec3f.inl>

#include <cetech/core/memory/memory.h>
#include <cetech/core/config.h>
#include <cetech/modules/resource/resource.h>

#include <cetech/core/module.h>

#include <cetech/modules/world/world.h>
#include <cetech/modules/entity/entity.h>
#include <cetech/modules/component/component.h>
#include <cetech/core/yaml.h>
#include <cetech/core/api.h>

//==============================================================================
// Globals
//==============================================================================

ARRAY_PROTOTYPE(component_compiler_t);
ARRAY_PROTOTYPE_N(struct component_clb, component_clb_t);

MAP_PROTOTYPE(component_compiler_t);
MAP_PROTOTYPE_N(struct component_clb, component_clb_t);


#define _G ComponentMaagerGlobals
static struct G {
    MAP_T(component_compiler_t) compiler_map;
    MAP_T(uint32_t) spawn_order_map;

    MAP_T(component_clb_t) component_clb;
} _G = {0};

IMPORT_API(memory_api_v0);
IMPORT_API(world_api_v0);


//==============================================================================
// Public interface
//==============================================================================

void component_register_compiler(uint64_t type,
                                 component_compiler_t compiler,
                                 uint32_t spawn_order) {
    MAP_SET(component_compiler_t, &_G.compiler_map, type, compiler);
    MAP_SET(uint32_t, &_G.spawn_order_map, type, spawn_order);
}

int component_compile(uint64_t type,
                      yaml_node_t body,
                      ARRAY_T(uint8_t) *data) {

    component_compiler_t compiler = MAP_GET(component_compiler_t,
                                            &_G.compiler_map, type, NULL);

    if (!compiler) {
        return 0;
    }

    return compiler(body, data);
}

uint32_t component_get_spawn_order(uint64_t type) {
    return MAP_GET(uint32_t, &_G.spawn_order_map, type, 0);
}

void component_register_type(uint64_t type,
                             struct component_clb clb) {
    MAP_SET(component_clb_t, &_G.component_clb, type, clb);

    world_callbacks_t wclb = {
            .on_created = clb.on_world_create,
            .on_destroy = clb.on_world_destroy,
            .on_update = clb.on_world_update,
    };

    world_api_v0.register_callback(wclb);
}

void component_spawn(world_t world,
                     uint64_t type,
                     entity_t *ent_ids,
                     uint32_t *cent,
                     uint32_t *ents_parent,
                     uint32_t ent_count,
                     void *data) {

    struct component_clb clb = MAP_GET(component_clb_t, &_G.component_clb,
                                       type, component_clb_null);

    if (!clb.spawner) {
        return;
    }

    clb.spawner(world, ent_ids, cent, ents_parent, ent_count, data);
}

void component_destroy(world_t world,
                       entity_t *ent,
                       uint32_t count) {

    const MAP_ENTRY_T(component_clb_t) *ce_it = MAP_BEGIN(component_clb_t,
                                                          &_G.component_clb);
    const MAP_ENTRY_T(component_clb_t) *ce_end = MAP_END(component_clb_t,
                                                         &_G.component_clb);
    while (ce_it != ce_end) {
        ce_it->value.destroyer(world, ent, count);
        ++ce_it;
    }
}

static void _set_property(uint64_t type,
                          world_t world,
                          entity_t entity,
                          uint64_t key,
                          struct property_value value) {

    struct component_clb clb = MAP_GET(component_clb_t, &_G.component_clb,
                                       type, component_clb_null);

    if (!clb.set_property) {
        return;
    }

    clb.set_property(world, entity, key, value);
}

static struct property_value _get_property(uint64_t type,
                                           world_t world,
                                           entity_t entity,
                                           uint64_t key) {

    struct property_value value = {PROPERTY_INVALID};

    struct component_clb clb = MAP_GET(component_clb_t, &_G.component_clb,
                                       type, component_clb_null);

    if (!clb.get_property) {
        return (struct property_value) {PROPERTY_INVALID};
    }

    return clb.get_property(world, entity, key);
}

static void _init_api(struct api_v0 *api_v0) {
    static struct component_api_v0 api = {0};
    api.component_register_compiler = component_register_compiler;
    api.component_compile = component_compile;
    api.component_get_spawn_order = component_get_spawn_order;
    api.component_register_type = component_register_type;
    api.component_spawn = component_spawn;
    api.component_destroy = component_destroy;
    api.set_property = _set_property;
    api.get_property = _get_property;


    api_v0->register_api("component_api_v0", &api);
}

static void _init(struct api_v0 *api_v0) {
    GET_API(api_v0, memory_api_v0);
    GET_API(api_v0, world_api_v0);


    _G = (struct G) {0};

    MAP_INIT(component_compiler_t, &_G.compiler_map,
             memory_api_v0.main_allocator());
    MAP_INIT(uint32_t, &_G.spawn_order_map, memory_api_v0.main_allocator());
    MAP_INIT(component_clb_t, &_G.component_clb,
             memory_api_v0.main_allocator());
}

static void _shutdown() {
    MAP_DESTROY(component_compiler_t, &_G.compiler_map);
    MAP_DESTROY(uint32_t, &_G.spawn_order_map);
    MAP_DESTROY(component_clb_t, &_G.component_clb);

    _G = (struct G) {0};
}

void *component_get_module_api(int api) {
    switch (api) {
        case PLUGIN_EXPORT_API_ID: {
            static struct module_api_v0 module = {0};

            module.init = _init;
            module.init_api = _init_api;
            module.shutdown = _shutdown;


            return &module;
        }

        default:
            return NULL;
    }
}