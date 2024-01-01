// Include raylib library
#include "raylib.h"

// Define some constants
#define SCREEN_WIDTH 1000 // Screen width in pixels
#define SCREEN_HEIGHT 700    // Screen height in pixels
#define MAX_ELEMENTS 10 // Maximum number of elements in the stack
#define ELEMENT_WIDTH 100 // Width of each element in the stack
#define ELEMENT_HEIGHT 50 // Height of each element in the stack
#define ELEMENT_GAP 10 // Gap between each element in the stack
#define BUTTON_WIDTH 150 // Width of each button
#define BUTTON_HEIGHT 50 // Height of each button
#define BUTTON_GAP 20 // Gap between each button
#define FONT_SIZE 20 // Font size for the text
    
// Define some colors
#define BACKGROUND_COLOR BLACK // Background color
#define ELEMENT_COLOR WHITE // Element color
#define BUTTON_COLOR DARKGRAY // Button color
#define TEXT_COLOR BLACK // Text color
#define MAX_COLOR RED // Color for highlighting the maximum element and button
#define MIN_COLOR BLUE // Color for highlighting the minimum element and button

// Define a struct for the stack
typedef struct Stack {
    int data[MAX_ELEMENTS]; // Array to store the data of the elements
    int top; // Index of the top element
    bool highlightMax; // Flag to indicate whether to highlight the maximum element
    bool highlightMin; // Flag to indicate whether to highlight the minimum element
} Stack;

// Function prototypes
void InitStack(Stack *stack); // Initialize the stack
void Push(Stack *stack, int value); // Push a value to the stack
int Pop(Stack *stack); // Pop a value from the stack
int Peek(Stack *stack); // Peek the top value of the stack
bool IsEmpty(Stack *stack); // Check if the stack is empty
bool IsFull(Stack *stack); // Check if the stack is full
int GetMax(Stack *stack); // Get the maximum value in the stack
int GetMin(Stack *stack); // Get the minimum value in the stack
void DrawStack(Stack *stack); // Draw the stack on the screen
void DrawButtons(Stack *stack); // Draw the buttons on the screen
void UpdateStack(Stack *stack); // Update the stack based on user input


// Main function
int main(void)
{
    // Initialize the window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Primitive Pile Visualization");

    // Initialize the stack
    Stack stack;
    InitStack(&stack);

    // Set the target FPS
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update the stack
        UpdateStack(&stack);
    

        // Begin drawing
        BeginDrawing();

        // Clear the background
        ClearBackground(BACKGROUND_COLOR);

        // Draw the stack
        DrawStack(&stack);

        // Draw the buttons
        DrawButtons(&stack);

        // End drawing
        EndDrawing();
    }

    // Close window and OpenGL context
    CloseWindow();

    return 0;
}

// Initialize the stack
void InitStack(Stack *stack)
{
    stack->top = -1; // Set the top index to -1
    stack->highlightMax = false; // Set the highlightMax flag to false
    stack->highlightMin = false; // Set the highlightMin flag to false
}

// Push a value to the stack
void Push(Stack *stack, int value)
{
    if (!IsFull(stack)) // Check if the stack is not full
    {
        stack->top++; // Increment the top index
        stack->data[stack->top] = value; // Store the value at the top index
    }
}

// Pop a value from the stack
int Pop(Stack *stack)
{
    int value = -1; // Initialize the value to -1
    if (!IsEmpty(stack)) // Check if the stack is not empty
    {
        value = stack->data[stack->top]; // Get the value at the top index
        stack->top--; // Decrement the top index
    }
    return value; // Return the value
}

// Peek the top value of the stack
int Peek(Stack *stack)
{
    int value = -1; // Initialize the value to -1
    if (!IsEmpty(stack)) // Check if the stack is not empty
    {
        value = stack->data[stack->top]; // Get the value at the top index
    }
    return value; // Return the value
}

// Check if the stack is empty
bool IsEmpty(Stack *stack)
{
    return (stack->top == -1); // Return true if the top index is -1
}

// Check if the stack is full
bool IsFull(Stack *stack)
{
    return (stack->top == MAX_ELEMENTS - 1); // Return true if the top index is the maximum index
}

// Get the maximum value in the stack
int GetMax(Stack *stack)
{
    int max = -1; // Initialize the maximum value to -1
    if (!IsEmpty(stack)) // Check if the stack is not empty
    {
        max = stack->data[0]; // Set the maximum value to the first element
        for (int i = 1; i <= stack->top; i++) // Loop through the rest of the elements
        {
            if (stack->data[i] > max) // If the current element is greater than the maximum value
            {
                max = stack->data[i]; // Update the maximum value
            }
        }
    }
    return max; // Return the maximum value
}

// Get the minimum value in the stack
int GetMin(Stack *stack)
{
    int min = -1; // Initialize the minimum value to -1
    if (!IsEmpty(stack)) // Check if the stack is not empty
    {
        min = stack->data[0]; // Set the minimum value to the first element
        for (int i = 1; i <= stack->top; i++) // Loop through the rest of the elements
        {
            if (stack->data[i] < min) // If the current element is less than the minimum value
            {
                min = stack->data[i]; // Update the minimum value
            }
        }
    }
    return min; // Return the minimum value
}

// Draw the stack on the screen
void DrawStack(Stack *stack)
{
    // Calculate the x coordinate of the stack
    int x = (SCREEN_WIDTH - ELEMENT_WIDTH) / 2;

    // Loop through the elements in the stack
    for (int i = 0; i <= stack->top; i++)
    {
        // Calculate the y coordinate of the current element
        int y =  SCREEN_HEIGHT - (i + 1) * (ELEMENT_HEIGHT + ELEMENT_GAP)  ;

        // Get the value of the current element
        int value = stack->data[i];

        // Check if the current element is the maximum or the minimum element
        bool isMax = (value == GetMax(stack)) && stack->highlightMax;
        bool isMin = (value == GetMin(stack)) && stack->highlightMin;

        // Choose the color of the current element based on the highlighting
        Color color = ELEMENT_COLOR;
        if (isMax) color = MAX_COLOR;
        if (isMin) color = MIN_COLOR;

        // Draw the current element as a rectangle
        DrawRectangle(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, color);

        // Draw the value of the current element as a text
        DrawText(TextFormat("%d", value), x + ELEMENT_WIDTH / 2 - 10, y + ELEMENT_HEIGHT / 2 - 10, FONT_SIZE, TEXT_COLOR);

        // Check if the mouse is over the current element
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT}))
        {
            // Draw a border around the current element
            DrawRectangleLines(x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT, TEXT_COLOR);
        }
    }
}

// Draw the buttons on the screen
void DrawButtons(Stack *stack)
{
    // Calculate the x coordinate of the buttons
    int x = (SCREEN_WIDTH - 4 * BUTTON_WIDTH - 3 * BUTTON_GAP) / 2;

    // Calculate the y coordinate of the buttons
    int y = 20;

    // Draw the "Add Element" button
    DrawRectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_COLOR);
    DrawText("Add Element", x + 10, y + 15, FONT_SIZE, TEXT_COLOR);

    // Draw the "Remove Element" button
    x += BUTTON_WIDTH + BUTTON_GAP;
    DrawRectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_COLOR);
    DrawText("Remove Element", x + 10, y + 15, FONT_SIZE, TEXT_COLOR);

    // Draw the "Highlight Max" button
    x += BUTTON_WIDTH + BUTTON_GAP; 
    DrawRectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_COLOR);
    DrawText(stack->highlightMax ? "Unhighlite Max" : "Highlight Max", x + 10, y + 15, 18, TEXT_COLOR);
  

    // Draw the "Highlight Min" button
    x += BUTTON_WIDTH + BUTTON_GAP; 
    DrawRectangle(x, y, BUTTON_WIDTH, BUTTON_HEIGHT, BUTTON_COLOR);
    DrawText(stack->highlightMin ? "Unhighlight Min" : "Highlight Min", x + 10, y + 15, 18, TEXT_COLOR);
   
    // Check if the mouse is over any button
    for (int i = 0; i < 4; i++)
    {
        // Calculate the x coordinate of the current button
        int bx = (SCREEN_WIDTH - 4 * BUTTON_WIDTH - 3 * BUTTON_GAP) / 2 + i * (BUTTON_WIDTH + BUTTON_GAP);

        // Check if the mouse is over the current button
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){bx, y, BUTTON_WIDTH, BUTTON_HEIGHT}))
        {
            // Draw a border around the current button
            DrawRectangleLines(bx, y, BUTTON_WIDTH, BUTTON_HEIGHT, TEXT_COLOR);
        }
    }
}




// Update the stack based on user input
void UpdateStack(Stack *stack)
{
    // Check if the left mouse button is pressed
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        // Get the mouse position
        Vector2 mouse = GetMousePosition();

        // Calculate the x coordinate of the buttons
        int x = (SCREEN_WIDTH - 4 * BUTTON_WIDTH - 3 * BUTTON_GAP) / 2;

        // Calculate the y coordinate of the buttons
        int y = 20;

        // Check if the mouse is over the "Add Element" button
        if (CheckCollisionPointRec(mouse, (Rectangle){x, y, BUTTON_WIDTH, BUTTON_HEIGHT}))
        {
            // Generate a random value between 1 and 100
            int value = GetRandomValue(1, 100);

            // Push the value to the stack
            Push(stack, value);
        }

        // Check if the mouse is over the "Remove Element" button
        x += BUTTON_WIDTH + BUTTON_GAP;
        if (CheckCollisionPointRec(mouse, (Rectangle){x, y, BUTTON_WIDTH, BUTTON_HEIGHT}))
        {
            // Pop the top value from the stack
            Pop(stack);
        }

        // Check if the mouse is over the "Highlight Max" button
        x += BUTTON_WIDTH + BUTTON_GAP;
        if (CheckCollisionPointRec(mouse, (Rectangle){x, y, BUTTON_WIDTH, BUTTON_HEIGHT}))
        {
            // Toggle the highlightMax flag
            stack->highlightMax = !stack->highlightMax;
            
            //added by meeeee
           
            // If the highlightMax flag is true, set the highlightMin flag to false
        
        }

        // Check if the mouse is over the "Highlight Min" button
        x += BUTTON_WIDTH + BUTTON_GAP;
        if (CheckCollisionPointRec(mouse, (Rectangle){x, y, BUTTON_WIDTH, BUTTON_HEIGHT}))
        {
            // Toggle the highlightMin flag
            stack->highlightMin = !stack->highlightMin;

            //added by meeeeee
           
            // If the highlightMin flag is true, set the highlightMax flag to false
           
        }

        // Calculate the x coordinate of the stack
        x = (SCREEN_WIDTH - ELEMENT_WIDTH) / 2;

        // Loop through the elements in the stack
        for (int i = 0; i <= stack->top; i++)
        {
            // Calculate the y coordinate of the current element
            y = SCREEN_HEIGHT - (i + 1) * (ELEMENT_HEIGHT + ELEMENT_GAP);

            // Check if the mouse is over the current element
            if (CheckCollisionPointRec(mouse, (Rectangle){x, y, ELEMENT_WIDTH, ELEMENT_HEIGHT}))
            {
                // Remove the current element from the stack
                for (int j = i; j < stack->top; j++)
                {
                    stack->data[j] = stack->data[j + 1];
                }
                stack->top--;
            }
        }
    }
}