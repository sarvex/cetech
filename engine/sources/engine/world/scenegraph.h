#ifndef CETECH_SCENE_GAPH_H
#define CETECH_SCENE_GAPH_H

#include <celib/stringid/types.h>
#include "engine/core/types.h"

typedef struct {
    u32 idx;
} scene_node_t;



int scenegraph_init(int stage);

void scenegraph_shutdown();

int scenegraph_is_valid(scene_node_t transform);

void scenegraph_transform(world_t world,
                          scene_node_t transform,
                          mat44f_t *parent);

vec3f_t scenegraph_get_position(world_t world,
                                scene_node_t transform);

quatf_t scenegraph_get_rotation(world_t world,
                                scene_node_t transform);


vec3f_t scenegraph_get_scale(world_t world,
                             scene_node_t transform);


mat44f_t *scenegraph_get_world_matrix(world_t world,
                                      scene_node_t transform);


void scenegraph_set_position(world_t world,
                             scene_node_t transform,
                             vec3f_t pos);


void scenegraph_set_rotation(world_t world,
                             scene_node_t transform,
                             quatf_t rot);


void scenegraph_set_scale(world_t world,
                          scene_node_t transform,
                          vec3f_t scale);

int scenegraph_has(world_t world,
                   entity_t entity);

scene_node_t scenegraph_get_root(world_t world,
                                 entity_t entity);

scene_node_t scenegraph_create(world_t world,
                               entity_t entity,
                               stringid64_t *names,
                               u32 *parent,
                               mat44f_t *pose,
                               u32 count);

void scenegraph_link(world_t world,
                     scene_node_t parent,
                     scene_node_t child);

scene_node_t scenegraph_node_by_name(world_t world,
                                     entity_t entity,
                                     stringid64_t name);

#endif //CETECH_SCENE_GAPH_H