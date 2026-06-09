#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CANVAS_WIDTH 80
#define CANVAS_HEIGHT 25
#define MAX_OBJECTS 100

typedef enum {
    EMPTY,
    LINE,
    CIRCLE,
    RECTANGLE,
    TRIANGLE
} ShapeType;

typedef struct {
    ShapeType type;
    int x1, y1, x2, y2;  // For line, rectangle
    int cx, cy, radius;  // For circle
    int active;          // Whether this object is active
} Shape;

char canvas[CANVAS_HEIGHT][CANVAS_WIDTH];
Shape objects[MAX_OBJECTS];
int object_count = 0;

// Initialize canvas with empty spaces
void initialize_canvas() {
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            canvas[i][j] = ' ';
        }
    }
}

// Display the canvas
void display_canvas() {
    printf("\n+");
    for (int j = 0; j < CANVAS_WIDTH; j++) printf("-");
    printf("+\n");
    
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        printf("|");
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("|\n");
    }
    
    printf("+");
    for (int j = 0; j < CANVAS_WIDTH; j++) printf("-");
    printf("+\n\n");
}

// Draw a line using Bresenham algorithm
void draw_line(int x1, int y1, int x2, int y2, char ch) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    
    int x = x1, y = y1;
    while (1) {
        if (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT) {
            canvas[y][x] = ch;
        }
        if (x == x2 && y == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

// Draw a circle using midpoint circle algorithm
void draw_circle(int cx, int cy, int radius, char ch) {
    int x = 0, y = radius;
    int d = 3 - 2 * radius;
    
    while (x <= y) {
        // Draw 8 octants
        if (cx + x >= 0 && cx + x < CANVAS_WIDTH && cy + y >= 0 && cy + y < CANVAS_HEIGHT)
            canvas[cy + y][cx + x] = ch;
        if (cx - x >= 0 && cx - x < CANVAS_WIDTH && cy + y >= 0 && cy + y < CANVAS_HEIGHT)
            canvas[cy + y][cx - x] = ch;
        if (cx + x >= 0 && cx + x < CANVAS_WIDTH && cy - y >= 0 && cy - y < CANVAS_HEIGHT)
            canvas[cy - y][cx + x] = ch;
        if (cx - x >= 0 && cx - x < CANVAS_WIDTH && cy - y >= 0 && cy - y < CANVAS_HEIGHT)
            canvas[cy - y][cx - x] = ch;
        if (cx + y >= 0 && cx + y < CANVAS_WIDTH && cy + x >= 0 && cy + x < CANVAS_HEIGHT)
            canvas[cy + x][cx + y] = ch;
        if (cx - y >= 0 && cx - y < CANVAS_WIDTH && cy + x >= 0 && cy + x < CANVAS_HEIGHT)
            canvas[cy + x][cx - y] = ch;
        if (cx + y >= 0 && cx + y < CANVAS_WIDTH && cy - x >= 0 && cy - x < CANVAS_HEIGHT)
            canvas[cy - x][cx + y] = ch;
        if (cx - y >= 0 && cx - y < CANVAS_WIDTH && cy - x >= 0 && cy - x < CANVAS_HEIGHT)
            canvas[cy - x][cx - y] = ch;
        
        if (d < 0) {
            d = d + 4 * x + 6;
        } else {
            d = d + 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

// Draw a rectangle
void draw_rectangle(int x1, int y1, int x2, int y2) {
    // Ensure x1 <= x2 and y1 <= y2
    if (x1 > x2) { int temp = x1; x1 = x2; x2 = temp; }
    if (y1 > y2) { int temp = y1; y1 = y2; y2 = temp; }
    
    // Draw top and bottom edges with _
    for (int x = x1; x <= x2; x++) {
        if (y1 >= 0 && y1 < CANVAS_HEIGHT && x >= 0 && x < CANVAS_WIDTH)
            canvas[y1][x] = '_';
        if (y2 >= 0 && y2 < CANVAS_HEIGHT && x >= 0 && x < CANVAS_WIDTH)
            canvas[y2][x] = '_';
    }
    
    // Draw left and right edges with *
    for (int y = y1; y <= y2; y++) {
        if (x1 >= 0 && x1 < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT)
            canvas[y][x1] = '*';
        if (x2 >= 0 && x2 < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT)
            canvas[y][x2] = '*';
    }
}

// Draw a triangle
void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
    draw_line(x1, y1, x2, y2, '*');
    draw_line(x2, y2, x3, y3, '*');
    draw_line(x3, y3, x1, y1, '*');
}

// Clear canvas for redrawing
void clear_canvas() {
    for (int i = 0; i < CANVAS_HEIGHT; i++) {
        for (int j = 0; j < CANVAS_WIDTH; j++) {
            canvas[i][j] = ' ';
        }
    }
}

// Redraw all active objects
void redraw_all() {
    clear_canvas();
    for (int i = 0; i < object_count; i++) {
        if (!objects[i].active) continue;
        
        switch (objects[i].type) {
            case LINE:
                draw_line(objects[i].x1, objects[i].y1, 
                         objects[i].x2, objects[i].y2, '*');
                break;
            case CIRCLE:
                draw_circle(objects[i].cx, objects[i].cy, 
                           objects[i].radius, '*');
                break;
            case RECTANGLE:
                draw_rectangle(objects[i].x1, objects[i].y1, 
                              objects[i].x2, objects[i].y2);
                break;
            case TRIANGLE:
                draw_triangle(objects[i].x1, objects[i].y1,
                             objects[i].x2, objects[i].y2,
                             objects[i].cx, objects[i].cy);
                break;
            default:
                break;
        }
    }
}

// Add a line object
void add_line() {
    if (object_count >= MAX_OBJECTS) {
        printf("Canvas is full!\n");
        return;
    }
    
    printf("Enter line coordinates (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &objects[object_count].x1, &objects[object_count].y1,
          &objects[object_count].x2, &objects[object_count].y2);
    
    objects[object_count].type = LINE;
    objects[object_count].active = 1;
    object_count++;
    
    redraw_all();
    printf("Line added successfully!\n");
}

// Add a circle object
void add_circle() {
    if (object_count >= MAX_OBJECTS) {
        printf("Canvas is full!\n");
        return;
    }
    
    printf("Enter circle parameters (cx cy radius): ");
    scanf("%d %d %d", &objects[object_count].cx, &objects[object_count].cy,
          &objects[object_count].radius);
    
    objects[object_count].type = CIRCLE;
    objects[object_count].active = 1;
    object_count++;
    
    redraw_all();
    printf("Circle added successfully!\n");
}

// Add a rectangle object
void add_rectangle() {
    if (object_count >= MAX_OBJECTS) {
        printf("Canvas is full!\n");
        return;
    }
    
    printf("Enter rectangle coordinates (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &objects[object_count].x1, &objects[object_count].y1,
          &objects[object_count].x2, &objects[object_count].y2);
    
    objects[object_count].type = RECTANGLE;
    objects[object_count].active = 1;
    object_count++;
    
    redraw_all();
    printf("Rectangle added successfully!\n");
}

// Add a triangle object
void add_triangle() {
    if (object_count >= MAX_OBJECTS) {
        printf("Canvas is full!\n");
        return;
    }
    
    printf("Enter triangle vertices (x1 y1 x2 y2 x3 y3): ");
    scanf("%d %d %d %d %d %d", &objects[object_count].x1, &objects[object_count].y1,
          &objects[object_count].x2, &objects[object_count].y2,
          &objects[object_count].cx, &objects[object_count].cy);
    
    objects[object_count].type = TRIANGLE;
    objects[object_count].active = 1;
    object_count++;
    
    redraw_all();
    printf("Triangle added successfully!\n");
}

// Delete an object
void delete_object() {
    printf("\nActive objects:\n");
    for (int i = 0; i < object_count; i++) {
        if (objects[i].active) {
            printf("%d: ", i);
            switch (objects[i].type) {
                case LINE: printf("Line (%d,%d) to (%d,%d)\n", objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2); break;
                case CIRCLE: printf("Circle at (%d,%d) radius %d\n", objects[i].cx, objects[i].cy, objects[i].radius); break;
                case RECTANGLE: printf("Rectangle (%d,%d) to (%d,%d)\n", objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2); break;
                case TRIANGLE: printf("Triangle\n"); break;
                default: break;
            }
        }
    }
    
    int id;
    printf("Enter object ID to delete: ");
    scanf("%d", &id);
    
    if (id >= 0 && id < object_count && objects[id].active) {
        objects[id].active = 0;
        redraw_all();
        printf("Object deleted successfully!\n");
    } else {
        printf("Invalid object ID!\n");
    }
}

// Modify an object
void modify_object() {
    printf("\nActive objects:\n");
    for (int i = 0; i < object_count; i++) {
        if (objects[i].active) {
            printf("%d: ", i);
            switch (objects[i].type) {
                case LINE: printf("Line (%d,%d) to (%d,%d)\n", objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2); break;
                case CIRCLE: printf("Circle at (%d,%d) radius %d\n", objects[i].cx, objects[i].cy, objects[i].radius); break;
                case RECTANGLE: printf("Rectangle (%d,%d) to (%d,%d)\n", objects[i].x1, objects[i].y1, objects[i].x2, objects[i].y2); break;
                case TRIANGLE: printf("Triangle\n"); break;
                default: break;
            }
        }
    }
    
    int id;
    printf("Enter object ID to modify: ");
    scanf("%d", &id);
    
    if (id < 0 || id >= object_count || !objects[id].active) {
        printf("Invalid object ID!\n");
        return;
    }
    
    switch (objects[id].type) {
        case LINE:
            printf("Enter new line coordinates (x1 y1 x2 y2): ");
            scanf("%d %d %d %d", &objects[id].x1, &objects[id].y1,
                  &objects[id].x2, &objects[id].y2);
            break;
        case CIRCLE:
            printf("Enter new circle parameters (cx cy radius): ");
            scanf("%d %d %d", &objects[id].cx, &objects[id].cy,
                  &objects[id].radius);
            break;
        case RECTANGLE:
            printf("Enter new rectangle coordinates (x1 y1 x2 y2): ");
            scanf("%d %d %d %d", &objects[id].x1, &objects[id].y1,
                  &objects[id].x2, &objects[id].y2);
            break;
        case TRIANGLE:
            printf("Enter new triangle vertices (x1 y1 x2 y2 x3 y3): ");
            scanf("%d %d %d %d %d %d", &objects[id].x1, &objects[id].y1,
                  &objects[id].x2, &objects[id].y2,
                  &objects[id].cx, &objects[id].cy);
            break;
        default:
            break;
    }
    
    redraw_all();
    printf("Object modified successfully!\n");
}

// Main menu
void show_menu() {
    printf("\n========== 2D Graphics Editor ==========\n");
    printf("1. Add Line\n");
    printf("2. Add Circle\n");
    printf("3. Add Rectangle\n");
    printf("4. Add Triangle\n");
    printf("5. Delete Object\n");
    printf("6. Modify Object\n");
    printf("7. Display Canvas\n");
    printf("8. Clear All\n");
    printf("9. Exit\n");
    printf("========================================\n");
    printf("Enter your choice: ");
}

int main() {
    initialize_canvas();
    int choice;
    
    while (1) {
        show_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                add_line();
                display_canvas();
                break;
            case 2:
                add_circle();
                display_canvas();
                break;
            case 3:
                add_rectangle();
                display_canvas();
                break;
            case 4:
                add_triangle();
                display_canvas();
                break;
            case 5:
                delete_object();
                display_canvas();
                break;
            case 6:
                modify_object();
                display_canvas();
                break;
            case 7:
                display_canvas();
                break;
            case 8:
                object_count = 0;
                initialize_canvas();
                printf("Canvas cleared!\n");
                break;
            case 9:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}