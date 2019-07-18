#include <ecs_backup.h>

#define MOVE_SPEED (5)

void MoveSquare(ecs_rows_t *rows) {
    ECS_COLUMN(rows, EcsInput, input, 1);
    ECS_COLUMN(rows, EcsPosition2D, position, 2);
    ECS_COLUMN_COMPONENT(rows, EcsPosition2D, 2);

    int x_v = input->keys[ECS_KEY_D].state || input->keys[ECS_KEY_RIGHT].state;
        x_v -= input->keys[ECS_KEY_A].state || input->keys[ECS_KEY_LEFT].state;
    int y_v = input->keys[ECS_KEY_S].state || input->keys[ECS_KEY_DOWN].state;
        y_v -= input->keys[ECS_KEY_W].state || input->keys[ECS_KEY_UP].state;

    position->x += x_v * MOVE_SPEED;
    position->y += y_v * MOVE_SPEED;

    if (input->mouse.left.pressed) {
        ecs_entity_t square = ecs_column_source(rows, 2);
        ecs_remove(rows->world, square, EcsPosition2D);
        ecs_add(rows->world, square, EcsPosition2D);
        printf("Restored from backup\n");
    } else if (input->mouse.right.pressed) {
        ECS_COLUMN_ENTITY(rows, backup, 3);
        ecs_remove(rows->world, backup, EcsPosition2D);
        ecs_add(rows->world, backup, EcsPosition2D);
        printf("Saved to backup\n");
    }
}

int main(int argc, char *argv[]) {
    ecs_world_t *world = ecs_init_w_args(argc, argv);

    ECS_IMPORT(world, FlecsComponentsTransform, ECS_2D);
    ECS_IMPORT(world, FlecsComponentsGeometry, ECS_2D);
    ECS_IMPORT(world, FlecsComponentsGraphics, ECS_2D);
    ECS_IMPORT(world, FlecsComponentsInput, ECS_2D);
    ECS_IMPORT(world, FlecsSystemsSdl2, ECS_2D);

    /* Define entity for square and square backup */
    ECS_ENTITY(world, Square, EcsPosition2D, EcsSquare, EcsColor);
    ECS_ENTITY(world, SquareBackup, EcsPosition2D, EcsColor);

    /* Define system that moves the square on keyboard input */
    ECS_SYSTEM(world, MoveSquare, EcsOnUpdate, EcsInput, Square.EcsPosition2D, .SquareBackup);

    /* Initialize canvas */
    ecs_set(world, 0, EcsCanvas2D, {
        .window = { .width = 800, .height = 600 }, .title = "Hello ecs_backup!" 
    });

    /* Initialize square */
    ecs_set(world, Square, EcsPosition2D, {0, 0});
    ecs_set(world, Square, EcsSquare, { .size = 50 });
    ecs_set(world, Square, EcsColor, { .r = 0, .g = 0, .b = 255, .a = 255 });

    /* Initialize square backup */
    ecs_set(world, SquareBackup, EcsPosition2D, {0, 0});
    ecs_set(world, SquareBackup, EcsSquare, { .size = 55 });
    ecs_set(world, SquareBackup, EcsColor, { .r = 255, .g = 0, .b = 255, .a = 255 });

    ecs_inherit(world, Square, SquareBackup);
    ecs_inherit(world, SquareBackup, Square);

    printf("Left click to restore from backup, right click to save to backup\n");

    /* Enter main loop */
    ecs_set_target_fps(world, 60);

    while ( ecs_progress(world, 0));

    /* Cleanup */
    return ecs_fini(world);
}
