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

ball_t *insert_avl(ball_t *ball, ball_t *a) {
    if (ball == NULL) ball = a;
    if (a->size < ball->size) return insert_avl(ball->left, a);
    if (a->size > ball->size) return insert_avl(ball->right, a);
    if (a->size == ball->size) return insert_avl(ball->left, a);

    int8_t bal = balance(ball);

    // Left heavy
    if (bal > 1 && a->size < ball->left->size)
        return rotate_right(ball);
    // Right heavy
    if (bal < -1 && a->size > ball->right->size)
        return rotate_left(ball);
    // Left-Right
    if (bal > 1 && a->size > ball->left->size) {
        ball->left = rotate_left(ball->left);
        return rotate_right(ball);
    }
    // Right-Left
    if (bal < -1 && a->size < ball->right->size) {
        ball->right = rotate_right(ball->right);
        return rotate_left(ball);
    }
    return ball;
}

ball_t *rotate_left(ball_t *ball) {
    ball_t *new_root = ball->right;
    ball->right      = new_root->left;
    new_root->left   = ball;
    return new_root;
}

ball_t *rotate_right(ball_t *ball) {
    ball_t *new_root = ball->left;
    ball->left       = new_root->right;
    new_root->right  = ball;
    return new_root;
}

ball_t *delete_val(ball_t *ball, size_t size) {
    if (ball == NULL) return NULL;

    if (size < ball->size)
        ball->left  = delete_val(ball->left,  size);
    else if (size > ball->size)
        ball->right = delete_val(ball->right, size);
    else {
        // Node found
        if (ball->left == NULL || ball->right == NULL) {
            ball_t *temp = ball->left ? ball->left : ball->right;
            // No child
            if (temp == NULL) {
                temp = ball;
                ball = NULL;
            } else {
                // One child: copy child into current node
                *ball = *temp;
            }
            free(temp);
        } else {
            // Two children: get in-order successor
            ball_t *temp = min_node(ball->right);
            ball->size   = temp->size;
            ball->right  = delete_val(ball->right, temp->size);
        }
    }

    if (ball == NULL) return NULL;

    // Rebalance
    int8_t bal = balance(ball);

    if (bal > 1 && balance(ball->left) >= 0)
        return rotate_right(ball);
    if (bal > 1 && balance(ball->left) < 0) {
        ball->left = rotate_left(ball->left);
        return rotate_right(ball);
    }
    if (bal < -1 && balance(ball->right) <= 0)
        return rotate_left(ball);
    if (bal < -1 && balance(ball->right) > 0) {
        ball->right = rotate_right(ball->right);
        return rotate_left(ball);
    }

    return ball;
}