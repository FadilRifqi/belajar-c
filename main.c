#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <raylib.h>
#include <raymath.h>

#define NOB_IMPLEMENTATION
#include "nob.h"

#define MIN_X -20
#define MAX_X 20
#define MIN_Y -20
#define MAX_Y 20
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 760
#define SAMPLE_RADIUS 4.0f
#define MEAN_RADIUS (SAMPLE_RADIUS*2)
#define K 5

static Vector2 project_sample_to_screen(Vector2 sample)
{
    float w = GetScreenWidth();
    float h = GetScreenHeight();
    return CLITERAL(Vector2){.x = (sample.x - MIN_X ) / (MAX_X - MIN_X) * w,
                             .y = h - (sample.y - MIN_Y ) / (MAX_Y - MIN_Y) * h
                             };
}

typedef struct {
    Vector2 *items;
    size_t count;
    size_t capacity;
} Samples;

static inline float rand_float(void)
{
    return (float)rand() / RAND_MAX;
}

static void generate_cluster(Vector2 center, float radius, size_t count, Samples *samples)
{
    for(size_t i = 0; i < count; i++) {
        float angle = rand_float()*PI*2;
        float mag = rand_float();
        Vector2 sample = {
            .x = center.x + cosf(angle) * radius * mag,
            .y = center.y + sinf(angle) * radius * mag
        };
        nob_da_append(samples, sample);
    }
}

static Color raylib_colors[]= {
    GOLD,
    PINK,
    MAROON,
    LIME,
    SKYBLUE,
    VIOLET,
};

#define colors_len NOB_ARRAY_LEN(raylib_colors)

static Samples clusters[K] = {0};
static Vector2 means[K] = {0};
static Samples set = {0};

static void generate_new_state();

static void reset_cluster();

static void update_means();

int main(void) {
    srand(time(0));
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Data Mining");

    generate_new_state();
    reset_cluster();

    while(!WindowShouldClose()) {
        if(IsKeyPressed(KEY_R))
        {
            generate_new_state();
            reset_cluster();
        }
        if(IsKeyPressed(KEY_SPACE))
        {
            update_means();
            reset_cluster();
        }
        BeginDrawing();
        ClearBackground(GetColor(0x181818AA));
        for (size_t i = 0; i < K; i++)
        {
            for (size_t j = 0; j < clusters[i].count; ++j)
            {
                Vector2 sample = clusters[i].items[j];
                DrawCircleV(project_sample_to_screen(sample), SAMPLE_RADIUS, raylib_colors[i%colors_len]);
            }

            Vector2 mean = means[i];
            DrawCircleV(project_sample_to_screen(mean), MEAN_RADIUS, raylib_colors[i%colors_len]);
        }
        EndDrawing();
    }
    return 0;
}

static void generate_new_state(void)
{
    set.count = 0;
    generate_cluster(CLITERAL(Vector2){0}, 10, 100, &set);
    generate_cluster(CLITERAL(Vector2){MIN_X*0.5f,MAX_Y*0.5f}, 5, 50, &set);
    generate_cluster(CLITERAL(Vector2){MAX_X*0.5f,MAX_Y*0.5f}, 5, 50, &set);
    for (size_t i = 0; i < K; i++)
    {
        means[i].x = Lerp(MIN_X, MAX_X, rand_float());
        means[i].y = Lerp(MIN_Y, MAX_Y, rand_float());
    }
}

static void reset_cluster(void)
{
    for (size_t j = 0; j < K; j++)
    {
        clusters[j].count = 0;
    }

    for (size_t i = 0; i < set.count; ++i)
    {
        Vector2 p = set.items[i];
        int k = -1;
        float s = __FLT_MAX__;
        for (size_t j = 0; j < K; j++)
        {
            Vector2 mean = means[j];
            float sm =Vector2LengthSqr(Vector2Subtract(p, mean));
            if(sm < s) {
                s = sm;
                k = j;
            }
        }
            nob_da_append(&clusters[k], p);
    }
}

static void update_means(void)
{
    for (size_t i = 0; i < K; ++i)
    {
        if (clusters[i].count > 0)
        {
            means[i] = Vector2Zero();
            for (size_t j = 0; j < clusters[i].count; ++j)
            {
                means[i] = Vector2Add(means[i], clusters[i].items[j]);
            }
            means[i].x /= clusters[i].count;
            means[i].y /= clusters[i].count;
        }else
        {
            means[i].x = Lerp(MIN_X, MAX_X, rand_float());
            means[i].y = Lerp(MIN_Y, MAX_Y, rand_float());
        }
    }
}
