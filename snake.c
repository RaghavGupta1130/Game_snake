#include <stdio.h>
#include <stdlib.h>

// global variables
int board_size = 20;
int score = 0;
char direction = '-';
char board_matrix[20][20];
struct snake *head = NULL;
struct food *apple = NULL;
// ------------------------------------------------------------
// struct snake declaration
struct snake {
    int data;
    int x;
    int y;
    struct snake *next;
};
// struct food declaration
struct food {
    char data;
    int x;
    int y;
};
// ------------------------------------------------------------
// print linked list
void print_list(){
    struct snake *node = head;
    while(node != NULL){
        printf("%c\n", node->data);
        node = node->next;
    }
}
// ------------------------------------------------------------
// print RULES
void print_rules(){
    printf("\nRULES FOR PLAYING\n");
    printf("Press U for going UP\n");
    printf("Press D for going DOWN\n");
    printf("Press R for going RIGHT\n");
    printf("Press L for going LEFT\n");
    printf("Press X for EXIT\n");
    printf("The game ends if you try to go beyond the play area\n");
    printf("The game ends if snake head touches its body\n");
    printf("ALL THE BEST !! \n\n");
}
// ------------------------------------------------------------
// FUNCTION: initial function to execute
void init() {
    for(int i = 0; i < board_size; i++){
        for(int j = 0; j < board_size; j++){
            board_matrix[i][j] = 'O';
        }
    }
    // initialising food
    apple = (struct food*)malloc(sizeof(struct food)); 
    apple->x = 0;
    apple->y = 0;
    apple->data = '@';

    // intialising snake
    struct snake *body = NULL;
    struct snake *tail = NULL;
    head = (struct snake*)malloc(sizeof(struct snake)); 
    body = (struct snake*)malloc(sizeof(struct snake)); 
    tail = (struct snake*)malloc(sizeof(struct snake)); 

    head->data = '#';
    head->x = 6;
    head->y = 6;
    head->next = body;

    body->data = '*';
    body->x = head->x + 1;
    body->y = head->y;
    body->next = tail;

    tail->data = '*';
    tail->x = body->x + 1;
    tail->y = body->y;
    tail->next = NULL;
}
// ------------------------------------------------------------
// FUNCTION: printing snake on board
void print_board() {
    for(int i = 0; i < board_size; i++){
        for(int j = 0; j < board_size; j++){
            board_matrix[i][j] = 'O';
        }
    }
    //printing snake
    struct snake *node = head;
    while(node != NULL){
        board_matrix[node->x][node->y] = node->data;
        node = node->next;
    }
    // printing food
    board_matrix[apple->x][apple->y] = apple->data;
    // printing remaining board;
    for(int i = 0; i < board_size; i++){
        for(int j = 0; j < board_size; j++){
            printf("%c ", board_matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nSCORE: %d\n", score);
}
// ----------------------------------------------------------
// FUNCTION: add node in front of linked list snake
void append_segment(int x, int y){
    struct snake *new_head = NULL;
    new_head = (struct snake*)malloc(sizeof(struct snake));
    new_head->data  = head->data; 
    new_head->x = x;
    new_head->y = y;
    new_head->next = head; 
    head = new_head; 
    head->next->data = '*';
}
// ----------------------------------------------------------
// FUNCTION: delete last node of snake
void delete_last_segment() {
    struct snake *ptr,*ptr1;
    ptr = head;   
    while(ptr->next != NULL)  
    {  
        ptr1 = ptr;  
        ptr = ptr ->next;  
    }  
    ptr1->next = NULL;  
    free(ptr); 
}
// --------------------------------------------------------------
// FUNCTION: show snake movement on board
void snake_move(int p, int q){
    append_segment(head->x + p, head->y + q);
    delete_last_segment();
    print_board();
}
// --------------------------------------------------------------
// FUNCTION: check if snake body forms a loop
int check_loop(int x, int y){
    struct snake *node = head;
    while(node != NULL){
        if(node->x == x && node->y == y){
            return 1;
        }
        node = node->next;
    }
    return 0;
}
// ------------------------------------------------------------
// FUNCTION: change the coordinates of position of food
void change_food_position(){
    int i = 0;
    int new_x = (apple->x % 15 + i);
    int new_y = (apple->y % 15 + i);
    while(check_loop(new_x, new_y)){
        new_x = (apple->x % 15 + i);
        new_y = (apple->y % 15 + i);
        i++;
    }
    apple->x = new_x;
    apple->y = new_y;
}
// ----------------------------------------------------------------
// FUNCTION: check if snake head goes outside the board
int check_border(int x, int y){
    if(x == board_size || y == board_size || x < 0 || y < 0){
        return 1;
    }
    return 0;
}
// ----------------------------------------------------------------
// FUNCTION: check the type of operation to be performed
void check_move(int p, int q){
    system("clear");
    int x = head->x + p;
    int y = head->y + q;
    struct snake *second_node = head->next;
    if(second_node->x == x && second_node->y == y){
        printf("\nINVALID\n");
        print_board();
        return;
    }
    else if(check_border(x, y)){
        direction = 'X';
        printf("\nHIT BORDER\nEND GAME\n");
        return;
    }
    else if(check_loop(x, y)){
        direction = 'X';
        printf("\nSNAKE BODY FORMS LOOP\nEND GAME\n");
        return;
    }
    else if(x == apple->x && y == apple->y){
        append_segment(head->x + p, head->y + q);
        change_food_position();
        score ++;
        print_board();
        return;
    }
    snake_move(p, q);
}
// ------------------------------------------------------------
// MAIN FUNCTION
int main()
{
    init();
    print_rules();
    print_board();
    while(direction != 'X'){
        scanf("%c", &direction);
        switch (direction){
            case 'L': 
                check_move(0, -1);
                //printf("left");
                break;
            case 'l': 
                check_move(0, -1);
                //printf("left");
                break;
            case 'R': 
                check_move(0, 1);
                //printf("right");
                break;
            case 'r': 
                check_move(0, 1);
                //printf("right");
                break;
            case 'U': 
                check_move(-1, 0);
                //printf("up");
                break;
            case 'u': 
                check_move(-1, 0);
                //printf("up");
                break;
            case 'D': 
                check_move(1, 0);
                //printf("down");
                break;
            case 'd': 
                check_move(1, 0);
                //printf("down");
                break;
        }
    }
    printf("\nSCORE: %d", score);
    return 0;
}