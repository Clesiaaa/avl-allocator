#include <stdio.h>
#include <../include/tools.h>

uint8_t height(ball_t *ball) {
    if (ball == NULL) return 0;
    return 1 + MAX(height(ball->left), height(ball->right));
}

int8_t balance(ball_t *ball) {
    if (ball == NULL) return 0;
    return height(ball->left) - height(ball->right);
}

/* REWORK
ball_t *insert_avl(ball_t *ball, ball_t *a) {
    printf("Not Implemented!");
};

ball_t *rotate_left(ball_t *ball) {
    printf("Not Implemented!");
};

ball_t *rotate_right(ball_t *ball) {
    printf("Not Implemented!");
};

ball_t *delete_val(ball_t *ball, size_t size) {
    printf("Not Implemented!");
};
*/