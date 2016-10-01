//==============================================================================
// Includes
//==============================================================================

#include "celib/containers/map.h"
#include <engine/world/world.h>
#include "engine/core/memory.h"

//==============================================================================
// Typedefs
//==============================================================================

ARRAY_T(world_t);
ARRAY_PROTOTYPE(world_callbacks_t);
ARRAY_PROTOTYPE(stringid64_t);


//==============================================================================
// Globals
//==============================================================================

#define _G WorldGlobals
static struct G {
    ARRAY_T(world_callbacks_t) callbacks;
    struct handlerid world_handler;
} _G = {0};


//==============================================================================
// Public interface
//==============================================================================

int world_init(int stage) {
    if (stage == 0) {
        return 1;
    }

    _G = (struct G) {0};

    ARRAY_INIT(world_callbacks_t, &_G.callbacks, memsys_main_allocator());

    handlerid_init(&_G.world_handler, memsys_main_allocator());

    return 1;
}

void world_shutdown() {
    handlerid_destroy(&_G.world_handler);
    ARRAY_DESTROY(world_callbacks_t, &_G.callbacks);
    _G = (struct G) {0};
}

void world_register_callback(world_callbacks_t clb) {
    ARRAY_PUSH_BACK(world_callbacks_t, &_G.callbacks, clb);
}

world_t world_create() {
    world_t w = {.h = handlerid_handler_create(&_G.world_handler)};

    for (int i = 0; i < ARRAY_SIZE(&_G.callbacks); ++i) {
        ARRAY_AT(&_G.callbacks, i).on_created(w);
    }

    return w;
}

void world_destroy(world_t world) {
    for (int i = 0; i < ARRAY_SIZE(&_G.callbacks); ++i) {
        ARRAY_AT(&_G.callbacks, i).on_destroy(world);
    }

    handlerid_handler_destroy(&_G.world_handler, world.h);
}