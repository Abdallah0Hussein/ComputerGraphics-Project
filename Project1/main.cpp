#include <GL/glut.h>
#include <cmath>

// Camera position
float camX = 0.0f, camY = 1.0f, camZ = 3.0f;
float camLookAtX = 0.0f, camLookAtY = 0.0f, camLookAtZ = 0.0f;
float angle = 0.0f;
float camRadius = 4.0f;

// Bicycle position and wheel rotation
float bikeAngle = 0.0f;
float wheelRotation = 0.0f;

// Animation control
bool animate = false;

// Door and window angles
float doorAngle = 0.0f;
float windowAngle = 0.0f;
float bikeX = 0.0f;
float bikeZ = 1.5f;
float varx = 1.5f, varz = 1.5f;
float rightWheelRotation= 0.0f;
float leftWheelRotation= 0.0f;
void drawCuboid(float x, float y, float z, float width, float height, float depth, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    // Front face
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x, y + height, z);
    // Back face
    glVertex3f(x, y, z - depth);
    glVertex3f(x + width, y, z - depth);
    glVertex3f(x + width, y + height, z - depth);
    glVertex3f(x, y + height, z - depth);
    // Top face
    glVertex3f(x, y + height, z);
    glVertex3f(x + width, y + height, z);
    glVertex3f(x + width, y + height, z - depth);
    glVertex3f(x, y + height, z - depth);
    // Bottom face
    glVertex3f(x, y, z);
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y, z - depth);
    glVertex3f(x, y, z - depth);
    // Right face
    glVertex3f(x + width, y, z);
    glVertex3f(x + width, y, z - depth);
    glVertex3f(x + width, y + height, z - depth);
    glVertex3f(x + width, y + height, z);
    // Left face
    glVertex3f(x, y, z);
    glVertex3f(x, y, z - depth);
    glVertex3f(x, y + height, z - depth);
    glVertex3f(x, y + height, z);
    glEnd();
}


void draw_Transformation_Window(float angele, float  x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(angele, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.2f, 0.0f, 0.0f);
    drawCuboid(-0.2f, 0.0f, 0.001f, 0.2f, 0.2f, 0.01f, 0.7f, 0.8f, 1.0f);
    glPopMatrix();
}
void draw_Const_Window(float  x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.2f, 0.0f, 0.0f);
    drawCuboid(-0.2f, 0.0f, 0.001f, 0.2f, 0.2f, 0.01f, 0.5f, 0.5f, 0.5f);
    glPopMatrix();
}
void init() {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}


void drawBuilding() {
    drawCuboid(-0.5f, -0.5f, 0.5f, 1.0f, 0.7f, 1.0f, 0.6f, 0.4f, 0.2f);
    drawCuboid(-0.5f, 0.0f, 0.5f, 1.0f, 0.7f, 1.0f, 0.6f, 0.4f, 0.2f);

    // Draw the roof above the house
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    // Front triangles
    glVertex3f(-0.5f, 0.7f, 0.5f);
    glVertex3f(0.5f, 0.7f, 0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.5f, 0.7f, -0.5f);
    glVertex3f(0.5f, 0.7f, -0.5f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    // Right triangle
    glVertex3f(0.5f, 0.7f, 0.5f);   // Top-right vertex
    glVertex3f(0.5f, 0.7f, -0.5f);  // Bottom-right vertex
    glVertex3f(0.0f, 1.0f, 0.0f);   // Top vertex
    // Left triangle
    glVertex3f(-0.5f, 0.7f, 0.5f);  // Top-left vertex
    glVertex3f(-0.5f, 0.7f, -0.5f); // Bottom-left vertex
    glVertex3f(0.0f, 1.0f, 0.0f);   // Top vertex
    glEnd();

    // Draw door
    glPushMatrix();
    glTranslatef(-0.1f, -0.5f, 0.5f);
    glRotatef(doorAngle, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.1f, 0.0f, 0.0f);
    drawCuboid(-0.1f, 0.0f, 0.001f, 0.2f, 0.3f, 0.01f, 0.3f, 0.3f, 0.3f);
    glPopMatrix();

    //    draw const door
    glPushMatrix();
    glTranslatef(-0.1f, -0.5f, 0.5f);
    glRotatef(0.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.1f, 0.0f, 0.0f);
    drawCuboid(-0.1f, 0.0f, 0.001f, 0.2f, 0.3f, 0.01f, 0.3f, 0.2f, 0.1f);
    glPopMatrix();

    //-----------------------------------------------------------------------------------------
    // Draw windows
    //    Transformation window 1
    draw_Transformation_Window(windowAngle, -0.4f, -0.1f, 0.5f);

    //    const window 1
    draw_Const_Window(-0.4f, -0.1f, 0.5f);
    //-----------------------------------------------------------------------------------------
    //    Transformation window 2
    draw_Transformation_Window(windowAngle, 0.2f, -0.1f, 0.5f);
    //    const window 2
    draw_Const_Window(0.2f, -0.1f, 0.5f);
    //-----------------------------------------------------------------------------------------
        //    Transformation window 3
    draw_Transformation_Window(windowAngle, -0.4f, 0.3f, 0.5f);
    //    const window 3
    draw_Const_Window(-0.4f, 0.3f, 0.5f);

    //-----------------------------------------------------------------------------------------
    //    Transformation window 4
    draw_Transformation_Window(windowAngle, 0.2f, 0.3f, 0.5f);
    //    const window 4
    draw_Const_Window(0.2f, 0.3f, 0.5f);
}

void drawWheel(float x, float y, float z, float radius) {
    glColor3f(0.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);
    glutSolidTorus(0.01f, radius, 12, 36);

    // Draw spokes
    glBegin(GL_LINES);
    for (int i = 0; i < 12; ++i) {
        float angle = i * (360.0f / 12);
        float radian = angle * 3.14159265358979323846f / 180.0f;
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(radius * cos(radian), radius * sin(radian), 0.0f);
    }
    glEnd();

    glPopMatrix();
}


void drawBicycle() {
    glColor3f(0.0f, 0.0f, 0.0f);
    // Draw frame
    glBegin(GL_LINES);

    glVertex3f(-0.2f, -0.3f, 0.3f);
    glVertex3f(0.2f, -0.3f, 0.3f);

    glVertex3f(0.0f, -0.3f, 0.3f);
    glVertex3f(0.0f, -0.1f, 0.3f);

    glVertex3f(0.0f, -0.1f, 0.3f);
    glVertex3f(0.2f, -0.3f, 0.3f);
    glEnd();
    // Draw wheels
    drawWheel(-0.2f, -0.3f, 0.3f, 0.1f);
    drawWheel(0.2f, -0.3f, 0.3f, 0.1f);
}

void updateCameraPosition() {
    camX = camRadius * sin(angle);
    camZ = camRadius * cos(angle);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(camX, camY, camZ, camLookAtX, camLookAtY, camLookAtZ, 0.0, 1.0, 0.0);

    drawBuilding();

    glPushMatrix();
    glTranslatef(bikeX, 0.0f, bikeZ);
    glRotatef(-bikeAngle * 180.0f / 3.14159265358979323846f, 0.0f, 1.0f, 0.0f);
    drawBicycle();
    glPopMatrix();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': camRadius -= 0.1f; break;
    case 's': camRadius += 0.1f; break;
    case 'a': angle -= 0.1f; break;
    case 'd': angle += 0.1f; break;
    case 'q': camY += 0.1f; break;
    case 'e': camY -= 0.1f; break;
    case 'f': varx += 0.1f; varz += 0.1f; break;
    case 'b': varx -= 0.1f; varz -= 0.1f; break;
    case 'r': rightWheelRotation += 10.0f; break;
    case 'l': leftWheelRotation += 10.0f; break;
    case 'o': doorAngle = -90.0f; break;
    case 'c': doorAngle = 0.0f; break;
    case 'O': windowAngle = -90.0f; break;
    case 'C': windowAngle = 0.0f; break;
    }
    updateCameraPosition();
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        animate = true;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        animate = false;
    }
}

void update(int value) {
    if (animate) {
        bikeAngle += 0.01f;
        if (bikeAngle >= 2 * 3.14159265358979323846f) {
            bikeAngle -= 2 * 3.14159265358979323846f;
        }
        bikeX = varx * cos(bikeAngle);
        bikeZ = varz * sin(bikeAngle);
        rightWheelRotation += 1.0f;
        leftWheelRotation += 1.0f;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("3D Building Scene");

    init();
    updateCameraPosition();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutTimerFunc(16, update, 0);
    glutMainLoop();
    return 0;
}