//! \defgroup World
//! Game world

#ifndef CETECH_WORLD_SYSTEM_H
#define CETECH_WORLD_SYSTEM_H

//==============================================================================
// Includes
//==============================================================================

#include "celib/handlerid.h"


//==============================================================================
// Typedefs
//==============================================================================

//! World handler
typedef struct {
    handler_t h;
} world_t;

//! On world create callback
//! \param world World
typedef void (*world_on_created_t)(world_t world);

//! On world destroy callback
//! \param world World
typedef void (*world_on_destroy_t)(world_t world);

//! On world update callback
//! \param world World
//! \param dt Delta time
typedef void (*world_on_update_t)(world_t world,
                                  float dt);

//! World callbacks
typedef struct {
    world_on_created_t on_created;  //!< On create
    world_on_destroy_t on_destroy;  //!< On destroy
    world_on_update_t on_update;    //!< On update
} world_callbacks_t;


//==============================================================================
// Api
//==============================================================================

//! World API V0
struct WorldApiV0 {

    //! Register world calbacks
    //! \param clb Callbacks
    void (*register_callback)(world_callbacks_t clb);

    //! Create new world
    //! \return New world
    world_t (*create)();

    //! Destroy world
    //! \param world World
    void (*destroy)(world_t world);

    //! Update world
    //! \param world World
    //! \param dt Delta time
    void (*update)(world_t world,
                   float dt);
};


#endif //CETECH_WORLD_SYSTEM_H
//! |}