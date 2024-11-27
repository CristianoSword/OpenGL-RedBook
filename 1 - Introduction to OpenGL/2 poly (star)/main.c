#include <windows.h>
#include <gl/gl.h>
#include <math.h>

#define PI 3.14159265358979323846 // Define constant for Pi

// Function prototypes
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

// Function to draw a star using OpenGL
void DrawStar() {
    glBegin(GL_TRIANGLE_FAN); // Begin drawing a fan of triangles (a filled shape)
    glColor3f(1.0, 1.0, 0.0); // Set the color to yellow

    // Central point of the star
    glVertex3f(0.5, 0.5, 0.0); // The center of the star

    // Vertices of the star
    for (int i = 0; i <= 10; i++) {
        float angle = i * PI / 5.0; // Calculate angle for each vertex
        float radius = (i % 2 == 0) ? 0.2 : 0.4; // Alternate between shorter and longer radius
        float x = 0.5 + radius * cos(angle); // Calculate the x coordinate of the vertex
        float y = 0.5 + radius * sin(angle); // Calculate the y coordinate of the vertex
        glVertex3f(x, y, 0.0); // Draw the vertex
    }

    glEnd(); // End drawing the star
}

// Main entry point of the Windows application
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* Register window class */
    wcex.cbSize = sizeof(WNDCLASSEX); // Specify the size of the WNDCLASSEX structure
    wcex.style = CS_OWNDC; // Style for the window (own device context)
    wcex.lpfnWndProc = WindowProc; // Window procedure function to handle messages
    wcex.cbClsExtra = 0; // No extra bytes for class
    wcex.cbWndExtra = 0; // No extra bytes for window
    wcex.hInstance = hInstance; // Application instance
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Load default application icon
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // Load default arrow cursor
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); // Set window background to black
    wcex.lpszMenuName = NULL; // No menu
    wcex.lpszClassName = "GLSample"; // Class name for the window
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // Load small application icon

    // Register the window class
    if (!RegisterClassEx(&wcex))
        return 0; // Return if registration fails

    /* Create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL 2nd Code - 17/09/2024 19:41",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          512,
                          512,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow); // Show the window

    /* Enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    /* Set up OpenGL viewport and projection */
    glMatrixMode(GL_PROJECTION); // Set the matrix mode to projection
    glLoadIdentity(); // Load the identity matrix
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0); // Set orthogonal projection for 2D rendering
    glMatrixMode(GL_MODELVIEW); // Switch to modelview matrix mode
    glLoadIdentity(); // Load the identity matrix for modelview

    /* Program main loop */
    while (!bQuit) // Continue until the user quits
    {
        /* Check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) // Check if there are any pending messages
        {
            /* Handle or dispatch messages */
            if (msg.message == WM_QUIT) // If message is quit
            {
                bQuit = TRUE; // Exit the loop
            }
            else
            {
                TranslateMessage(&msg); // Translate the message
                DispatchMessage(&msg); // Dispatch the message to the window procedure
            }
        }
        else
        {
            /* OpenGL animation code */
            glClearColor(0.5, 0.7, 1.0, 1.0); // Set background color (cyan)
            glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

            DrawStar(); // Call the function to draw the star

            glFlush(); // Ensure all OpenGL commands are executed
            SwapBuffers(hDC); // Swap the front and back buffers

            theta += 1.0f; // Increment the angle for animation
            Sleep(1); // Sleep for 1 millisecond to limit the animation speed
        }
    }

    /* Shut down OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* Destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam; // Return the message's wParam
}

// Window procedure function to handle window messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE: // If the window is being closed
            PostQuitMessage(0); // Post a quit message to terminate the loop
            break;

        case WM_DESTROY: // If the window is destroyed
            return 0; // Return 0 to indicate that the message was processed

        case WM_KEYDOWN: // If a key is pressed
        {
            switch (wParam) // Check which key was pressed
            {
                case VK_ESCAPE: // If the escape key is pressed
                    PostQuitMessage(0); // Post a quit message to terminate the loop
                    break;
            }
        }
        break;

        default: // Default case to handle other messages
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0; // Return 0 to indicate the message was handled
}

// Function to enable OpenGL rendering for the window
void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd; // Pixel format descriptor
    int iFormat;

    /* Get the device context (DC) */
    *hDC = GetDC(hwnd); // Get the device context for the window

    /* Set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd)); // Initialize the descriptor to 0

    pfd.nSize = sizeof(pfd); // Set the size of the descriptor
    pfd.nVersion = 1; // Set the version to 1
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER; // Set flags for OpenGL
    pfd.iPixelType = PFD_TYPE_RGBA; // Set the pixel type to RGBA
    pfd.cColorBits = 24; // Set the color depth to 24 bits
    pfd.cDepthBits = 16; // Set the depth buffer to 16 bits
    pfd.iLayerType = PFD_MAIN_PLANE; // Set layer type to main plane

    iFormat = ChoosePixelFormat(*hDC, &pfd); // Choose the best pixel format

    SetPixelFormat(*hDC, iFormat, &pfd); // Set the chosen pixel format

    /* Create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC); // Create the OpenGL rendering context
    wglMakeCurrent(*hDC, *hRC); // Make the rendering context current
}

// Function to disable OpenGL rendering and clean up
void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL); // Unset the OpenGL context
    wglDeleteContext(hRC); // Delete the OpenGL rendering context
    ReleaseDC(hwnd, hDC); // Release the device context
}
