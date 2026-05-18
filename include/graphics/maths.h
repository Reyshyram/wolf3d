/*
** EPITECH PROJECT, 2025
** graphics/maths.h
** File description:
** Maths for the engine
*/

#ifndef GRAPHICS_MATHS_H
// clang-format off
    #define GRAPHICS_MATHS_H

    #include <SFML/Graphics/Rect.h>
    #include <SFML/Graphics/Types.h>
    #include <SFML/System/Vector2.h>
    #include <math.h>

    #define M_PI 3.14159265358979323846
    #define MIN(a, b) (((a) < (b)) ? (a) : (b))
// clang-format on

static inline void vector_add(sfVector2f *a, sfVector2f *b, sfVector2f *result)
{
    result->x = a->x + b->x;
    result->y = a->y + b->y;
}

static inline void vector_subtract(sfVector2f *a, sfVector2f *b,
    sfVector2f *result)
{
    result->x = a->x - b->x;
    result->y = a->y - b->y;
}

static inline float vector_distance(sfVector2f *a, sfVector2f *b)
{
    const float dx = b->x - a->x;
    const float dy = b->y - a->y;

    return sqrtf(dx * dx + dy * dy);
}

static inline void vector_scale(sfVector2f *v, float scale, sfVector2f *result)
{
    result->x = v->x * scale;
    result->y = v->y * scale;
}

static inline void vector_normalize(sfVector2f *v, sfVector2f *result)
{
    const float length = sqrtf(v->x * v->x + v->y * v->y);

    if (length != 0) {
        result->x = v->x / length;
        result->y = v->y / length;
    } else {
        result->x = 0;
        result->y = 0;
    }
}

static inline float angle_between_points(sfVector2f *a, sfVector2f *b)
{
    const float dy = b->y - a->y;
    const float dx = b->x - a->x;
    const float angle_rad = atan2f(dy, dx);
    const float angle_deg = angle_rad * (180.0F / (float) M_PI);

    return angle_deg;
}

static inline float interpolatef(float a, float b, float t)
{
    return a + t * (b - a);
}

static inline bool rect_intersects(sfFloatRect *a, sfFloatRect *b)
{
    return (a->left <= b->left + b->width && a->left + a->width >= b->left
        && a->top <= b->top + b->height && a->top + a->height >= b->top);
}

static inline bool rect_contains(sfFloatRect *rect, sfVector2f *pos)
{
    return (pos->x >= rect->left && pos->x < rect->left + rect->width
        && pos->y >= rect->top && pos->y < rect->top + rect->height);
}

#endif /* !GRAPHICS_MATHS_H */
