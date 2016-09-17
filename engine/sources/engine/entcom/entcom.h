#ifndef CETECH_ENTITY_MANAGER_H
#define CETECH_ENTITY_MANAGER_H

//==============================================================================
// Includes
//==============================================================================

#include "celib/stringid/types.h"
#include "types.h"
#include "celib/yaml/yaml.h"
#include "engine/world_system/types.h"
#include "engine/entcom/types.h"

int entcom_init();

void entcom_shutdown();


//==============================================================================
// Entity interface
//==============================================================================

entity_t entity_manager_create();

void entity_manager_destroy(entity_t entity);

int entity_manager_alive(entity_t entity);

//==============================================================================
// Entity interface
//==============================================================================

void component_register_compiler(stringid64_t type,
                                 component_compiler_t compiler,
                                 u32 spawn_order);

int component_compile(stringid64_t type,
                      yaml_node_t body,
                      ARRAY_T(u8) *data);

u32 component_get_spawn_order(stringid64_t type);

void component_register_type(stringid64_t type,
                             component_spawner_t spawner,
                             component_destroyer_t destroyer,
                             component_on_world_create_t on_world_create,
                             component_on_world_destroy_t on_world_destroy);

void component_spawn(world_t world,
                     stringid64_t type,
                     entity_t *ent_ids,
                     entity_t *ents_parent,
                     u32 ent_count,
                     void *data);

//public static void DestroyAllType(int world, int[] ent_ids)


#endif //CETECH_ENTITY_MANAGER_H