#ifndef CELIB_MATH_TYPES_H
#define CELIB_MATH_TYPES_H

//==============================================================================
// Includes
//==============================================================================

#include "types.h"


//==============================================================================
// Vectors
//==============================================================================

typedef struct {
    union {
        float f[2];
        struct {
            float x;
            float y;
        };
    };
} cel_vec2f_t;


typedef struct {
    union {
        float f[3];
        struct {
            float x;
            float y;
            float z;
        };
    };
} cel_vec3f_t;

typedef struct {
    union {
        float f[4];
        struct {
            float x;
            float y;
            float z;
            float w;
        };
    };
} cel_vec4f_t;

//==============================================================================
// Quaternion
//==============================================================================

typedef cel_vec4f_t cel_quatf_t;


//==============================================================================
// Matrix
//==============================================================================

typedef struct {
    union {
        float f[3 * 3];
        struct {
            cel_vec3f_t x;
            cel_vec3f_t y;
            cel_vec3f_t z;
        };
    };
} mat33f_t;


typedef struct {
    union {
        float f[4 * 4];
        struct {
            cel_vec4f_t x;
            cel_vec4f_t y;
            cel_vec4f_t z;
            cel_vec4f_t w;
        };
    };
} cel_mat44f_t;

#endif //CELIB_MATH_TYPES_H