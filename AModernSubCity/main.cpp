#include <cstdio>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;
float CloudX = 0;
float CloudY = 0;

float CarX_R = 0;
float CarY_R = 0;

float CarX_L = 0;
float CarY_L = 0;

float sunX = 0;
float sunY = 0;

float moonX = 0;
float moonY = 0;
float rain = 0.0;
bool isDay = true;
bool moveCloudRight = false;

bool makeItNight = false;
bool makeItDay = false;
bool sunSitThere = false;
bool moonSitThere = false;
bool rainday = false;
bool isStopCondition = false;
void wheel(int x, int y, int outer, int inner);
void DrawCircle(float cx, float cy, float r, int num_segments)
///x= center,y= circle position,r= radious, segment= how many segment of line for smooth
{

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments); //get the current angle

        float x = r * cosf(theta); //calculate the x component
        float y = r * sinf(theta); //calculate the y component

        glVertex2f(x + cx, y + cy); //output vertex
    }
    glEnd();
}
void text(int x, int y, char *string)
{
    glColor3f(0.0, 0.0, 0.0);
    glRasterPos2f(x, y);
    int len, i;
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
    }
}
void Rain(int value)
{

    if (rainday)
    {

        rain += 0.01f;

        glBegin(GL_POINTS);
        for (int i = 1; i <= 10000; i++)
        {
            int x = rand(), y = rand();
            x %= 2000;
            y %= 2000;
            glBegin(GL_LINES);
            glColor3f(0.0, 1.0, 1.0);
            glVertex2d(x, y);
            glVertex2d(x + 5, y + 5);
            glEnd();
        }
    }
}
void Daysky()
{

    ///sky block
    glColor3ub(219, 223, 226);
    glBegin(GL_QUADS);
    glVertex2i(0, 600);
    glVertex2i(0, 145);
    glVertex2i(1200, 145);
    glVertex2i(1200, 600);
    glEnd();
}
void EveningSky()
{
    ///sky block
    glColor3ub(219, 223, 226);
    glBegin(GL_QUADS);
    glVertex2i(0, 145);
    glVertex2i(1200, 145);
    glColor3ub(219, 223, 226);
    glVertex2i(1200, 600);
    glVertex2i(0, 600);
    glEnd();
}
void Nightsky()
{

    ///sky block
    glColor3ub(0, 127, 179);
    glBegin(GL_QUADS);
    glVertex2i(0, 600);
    glVertex2i(0, 145);
    glVertex2i(1200, 145);
    glVertex2i(1200, 600);
    glEnd();
}
void sun()
{
    glPushMatrix();
    glTranslated(0, -300, 0);
    glColor3f(3.0, 1.0, 0.5);
    DrawCircle(805, 546, 50, 2000);
    glPopMatrix();
}
void moon()
{
    glPushMatrix();
    glTranslated(0, -200, 0);
    glColor3ub(251, 163, 31);
    DrawCircle(1060, 402, 30, 2000);
    glColor3ub(0, 127, 179);
    DrawCircle(960, 405, 30, 2000);
    glPopMatrix();
}
void coverTheSun()
{
    glColor3ub(219, 223, 226);
    glBegin(GL_QUADS);
    glVertex2i(730, 590);
    glVertex2i(730, 130);
    glVertex2i(860, 130);
    glVertex2i(860, 590);
    glEnd();
}
void coverThemoon()
{
    glColor3ub(0, 127, 179);
    glBegin(GL_QUADS);
    glVertex2i(710, 530);
    glVertex2i(710, 130);
    glVertex2i(1010, 130);
    glVertex2i(1010, 530);
    glEnd();
}
struct cloud
{
    void drawDayCloud()
    {
        glColor3f(1.0, 1.0, 1.0); /// white
        DrawCircle(246, 486, 23, 2000); //1
        DrawCircle(290, 509, 40, 2000); //2
        DrawCircle(350, 494, 36, 2000); //3
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_QUADS);
        glVertex2i(246, 480);
        glVertex2i(246, 463);
        glVertex2i(350, 459);
        glVertex2i(350, 480);
        glEnd();
    }
    void drawNightCloud()
    {
        glColor3ub(36, 138, 197); /// sky blue
        DrawCircle(246, 486, 23, 2000); //1
        DrawCircle(290, 509, 40, 2000); //2
        DrawCircle(350, 494, 36, 2000); //3
        glColor3ub(36, 138, 197);
        glBegin(GL_QUADS);
        glVertex2i(246, 480);
        glVertex2i(246, 463);
        glVertex2i(350, 459);
        glVertex2i(350, 480);
        glEnd();
    }
};



struct LampPost
{
    void drawdayLampPost()
    {
        glColor3ub(103,154,169);
        glBegin(GL_TRIANGLES);
        glVertex2i(204,120);
        glVertex2i(215,120);
        glVertex2i(210,135);
        glEnd();

        glColor3ub(49,46,55);
        glBegin(GL_QUADS);
        glVertex2i(208,129);
        glVertex2i(212,129);
        glVertex2i(212,200);
        glVertex2i(208,200);
        glEnd();

        glColor3ub(49,46,55);
        glBegin(GL_TRIANGLES);
        glVertex2i(210,195);
        glVertex2i(215,205);
        glVertex2i(205,205);
        glEnd();

        glColor3ub(241,237,216);
        glBegin(GL_QUADS);
        glVertex2i(204,204);
        glVertex2i(215,204);
        glVertex2i(215,213);
        glVertex2i(204,213);
        glEnd();

        glColor3ub(49,46,55);
        glBegin(GL_QUADS);
        glVertex2i(208,214);
        glVertex2i(212,214);
        glVertex2i(212,222);
        glVertex2i(208,222);
        glEnd();

        glColor3ub(49,46,55);
        glLineWidth(4);
        glBegin(GL_LINES);
        glVertex2i(204,215);
        glVertex2i(215,215);
        glVertex2i(204,120);
        glVertex2i(215,120);
        glVertex2i(208,204);
        glVertex2i(212,204);
        glEnd();
    }
    void drawnightLampPost()
    {
        glColor3ub(103,154,169);
        glBegin(GL_TRIANGLES);
        glVertex2i(204,120);
        glVertex2i(215,120);
        glVertex2i(210,135);
        glEnd();

        glColor3ub(49,46,55);
        glBegin(GL_QUADS);
        glVertex2i(208,129);
        glVertex2i(212,129);
        glVertex2i(212,200);
        glVertex2i(208,200);
        glEnd();

        glColor3ub(49,46,55);
        glBegin(GL_TRIANGLES);
        glVertex2i(210,195);
        glVertex2i(215,205);
        glVertex2i(205,205);
        glEnd();

        glColor3ub(255,207,88);
        glBegin(GL_QUADS);
        glVertex2i(204,204);
        glVertex2i(215,204);
        glVertex2i(215,213);
        glVertex2i(204,213);
        glEnd();

        glColor3ub(49,46,55);
        glBegin(GL_QUADS);
        glVertex2i(208,214);
        glVertex2i(212,214);
        glVertex2i(212,222);
        glVertex2i(208,222);
        glEnd();

        glColor3ub(49,46,55);
        glLineWidth(4);
        glBegin(GL_LINES);
        glVertex2i(204,215);
        glVertex2i(215,215);
        glVertex2i(204,120);
        glVertex2i(215,120);
        glVertex2i(208,204);
        glVertex2i(212,204);
        glEnd();
    }

};

void dayLampPost()
{
    LampPost lp;

    glPushMatrix();
    glTranslated(20, 5, 0);
    lp.drawdayLampPost();
    glPopMatrix();

    glPushMatrix();
    glTranslated(340,5, 0);
    lp.drawdayLampPost();
    glPopMatrix();

    glPushMatrix();
    glTranslated(700, 5, 0);
    lp.drawdayLampPost();
    glPopMatrix();
}

void nightLampPost()
{
    LampPost lp;

    glPushMatrix();
    glTranslated(20, 5, 0);
    lp.drawnightLampPost();
    glPopMatrix();

    glPushMatrix();
    glTranslated(340,5, 0);
    lp.drawnightLampPost();
    glPopMatrix();

    glPushMatrix();
    glTranslated(700, 5, 0);
    lp.drawnightLampPost();
    glPopMatrix();
}



void DayCloud()
{
    cloud c;
    //cloud 1
    glPushMatrix();
    glTranslated(300, -50, 0); /// moving pixel
    c.drawDayCloud();
    glPopMatrix();
    //cloud 2
    glPushMatrix();
    glTranslated(-120, -15, 0); /// movung
    c.drawDayCloud();
    glPopMatrix();
    //cloud 3
    glPushMatrix();
    glTranslated(200, 50, 0);/// moving
    c.drawDayCloud();
    glPopMatrix();
    //cloud 4
    glPushMatrix();
    glTranslated(600, -100, 0);/// moving
    c.drawDayCloud();
    glPopMatrix();
}

void NightCloud()
{
    cloud c;
    //cloud 1
    glPushMatrix();
    glTranslated(300, -50, 0);
    c.drawNightCloud();
    glPopMatrix();
    //cloud 2
    glPushMatrix();
    glTranslated(-120,-15, 0);
    c.drawNightCloud();
    glPopMatrix();
    //cloud 3
    glPushMatrix();
    glTranslated(200, 50, 0);
    c.drawNightCloud();
    glPopMatrix();
    //cloud 4
    glPushMatrix();
    glTranslated(600, -100, 0);
    c.drawNightCloud();
    glPopMatrix();
}
struct cars
{
    void dayCarsRight()
    {
        //car01
        glColor3ub(0,0,0); /// lower part black
        glBegin(GL_QUADS);
        glVertex2i(104, 26);
        glVertex2i(196, 26);
        glVertex2i(196, 90);
        glVertex2i(104, 90);
        glEnd();

        glColor3ub(0,0,0); /// front
        glBegin(GL_POLYGON);
        glVertex2i(196, 26);
        glVertex2i(226, 26);
        glVertex2i(226, 50);
        glVertex2i(210, 65);
        glVertex2i(203, 80);
        glVertex2i(196, 85);
        glEnd();

        glColor3ub(240, 109, 35);/// container
        glBegin(GL_QUADS);
        glVertex2i(104, 32);
        glVertex2i(196, 32);
        glVertex2i(196, 90);
        glVertex2i(104, 90);
        glEnd();

        //car 01 window
        glColor3ub(253, 231, 215);
        glBegin(GL_QUADS);
        glVertex2i(196, 76);
        glVertex2i(196, 61);
        glVertex2i(218, 57);
        glVertex2i(206, 72);
        glEnd();

        text(125, 53, "DARAZ");

        wheel(123, 31, 8, 5);
        wheel(175, 31, 8, 5);



    }
    void dayCarLeft()
    {
        //car02
        glColor3ub(215, 236, 240);/// main body
        glBegin(GL_POLYGON);
        glVertex2i(535, 82);
        glVertex2i(525, 82);
        glVertex2i(518, 78);
        glVertex2i(518, 74);
        glVertex2i(518, 74);
        glVertex2i(604, 74);
        glVertex2i(604, 78);
        glVertex2i(599, 82);
        glVertex2i(590, 82);
        glVertex2i(584, 106);
        glVertex2i(541, 106);
        glEnd();

        glColor3ub(44, 136, 133); ///car2 window 01
        glBegin(GL_POLYGON);
        glVertex2i(546, 101);
        glVertex2i(541, 84);
        glVertex2i(561, 84);
        glVertex2i(561, 101);
        glEnd();

        glColor3ub(23, 125, 117); //car2 window 01 Glitch
        glBegin(GL_TRIANGLES);
        glVertex2i(546, 101);
        glVertex2i(561, 84);
        glVertex2i(561, 101);
        glEnd();

        glColor3ub(44, 136, 133); //car2 window 02
        glBegin(GL_POLYGON);
        glVertex2i(565, 101);
        glVertex2i(565, 84);
        glVertex2i(585, 84);
        glVertex2i(580, 101);
        glEnd();

        glColor3ub(23, 125, 117); //car2 window 02 Glitch
        glBegin(GL_TRIANGLES);
        glVertex2i(565, 101);
        glVertex2i(585, 84);
        glVertex2i(580, 101);
        glEnd();
        wheel(540, 74, 4, 2);
        wheel(578, 74, 4, 2);
    }
    void nightCarsRight()
    {
        //car01

        glColor3ub(108, 100, 110); ///head light
        glBegin(GL_TRIANGLES);
        glVertex2i(300, 40);
        glVertex2i(300, 15);
        glColor3ub(204, 169, 48);
        glVertex2i(200, 40);
        glEnd();

        glColor3ub(0,0,0); /// lower part black
        glBegin(GL_QUADS);
        glVertex2i(104, 26);
        glVertex2i(196, 26);
        glVertex2i(196, 90);
        glVertex2i(104, 90);
        glEnd();

        glColor3ub(121, 182, 231);/// front
        glBegin(GL_POLYGON);
        glVertex2i(196, 26);
        glVertex2i(226, 26);
        glVertex2i(226, 50);
        glVertex2i(210, 65);
        glVertex2i(203, 80);
        glVertex2i(196, 85);
        glEnd();

        glColor3ub(0, 137, 191);/// container
        glBegin(GL_QUADS);
        glVertex2i(104, 32);
        glVertex2i(196, 32);
        glVertex2i(196, 90);
        glVertex2i(104, 90);
        glEnd();

        //car 01 window
        glColor3ub(253, 231, 215);
        glBegin(GL_QUADS);
        glVertex2i(196, 76);
        glVertex2i(196, 61);
        glVertex2i(218, 57);
        glVertex2i(206, 72);
        glEnd();

        text(125, 53, "DARAZ");

        wheel(123, 31, 8, 5);
        wheel(175, 31, 8, 5);

    }
    void nightCarsLeft()
    {
        //car02
        glColor3ub(108, 100, 110); ///head light
        glBegin(GL_TRIANGLES);
        glVertex2i(472, 85);
        glVertex2i(472, 70);
        glColor3ub(204, 169, 48);
        glVertex2i(540, 79);
        glEnd();

        glColor3ub(4, 139, 182);
        glBegin(GL_POLYGON);
        glVertex2i(535, 82);
        glVertex2i(525, 82);
        glVertex2i(518, 78);
        glVertex2i(518, 74);
        glVertex2i(518, 74);
        glVertex2i(604, 74);
        glVertex2i(604, 78);
        glVertex2i(599, 82);
        glVertex2i(590, 82);
        glVertex2i(584, 106);
        glVertex2i(541, 106);
        glEnd();

        glColor3ub(6, 99, 157); //car2 window 01
        glBegin(GL_POLYGON);
        glVertex2i(546, 101);
        glVertex2i(541, 84);
        glVertex2i(561, 84);
        glVertex2i(561, 101);
        glEnd();

        glColor3ub(0, 30, 45); //car2 window 01 Glitch
        glBegin(GL_TRIANGLES);
        glVertex2i(546, 101);
        glVertex2i(561, 84);
        glVertex2i(561, 101);
        glEnd();

        glColor3ub(6, 99, 157); //car2 window 02
        glBegin(GL_POLYGON);
        glVertex2i(565, 101);
        glVertex2i(565, 84);
        glVertex2i(585, 84);
        glVertex2i(580, 101);
        glEnd();

        glColor3ub(0, 30, 45); //car2 window 02 Glitch
        glBegin(GL_TRIANGLES);
        glVertex2i(565, 101);
        glVertex2i(585, 84);
        glVertex2i(580, 101);
        glEnd();
        wheel(540, 74, 4, 2);
        wheel(578, 74, 4, 2);
    }
};
void moveCarRight()
{
    cars c;
    if (isStopCondition) // General stop condition
    {
        CarX_R += 0; // Car does not move
    }
    else
    {
        CarX_R += 0.9; /// Move car to the right(speed)
    }

    if (CarX_R > 1200)
    {
        CarX_R = -800; // Reset car position when it moves off screen
    }

    glPushMatrix();
    glTranslatef(CarX_R, CarY_R, 0); // Apply transformation for the car's position
    if (isDay)
    {
        c.dayCarsRight(); // Display daytime cars
    }
    else
    {
        c.nightCarsRight(); // Display nighttime cars
    }
    glPopMatrix();
}

void moveCarLeft()
{
    cars c;
    if (isStopCondition) // General stop condition
    {
        CarX_L += 0; // Car does not move
    }
    else
    {
        CarX_L -= 0.9; /// Move car to the left (speed)
    }

    if (CarX_L < -800)
    {
        CarX_L = 650; // Reset car position when it moves off screen
    }

    glPushMatrix();
    glTranslatef(CarX_L, CarY_L, 0); // Apply transformation for the car's position
    if (isDay)
    {
        c.dayCarLeft(); // Display daytime cars
    }
    else
    {
        c.nightCarsLeft(); // Display nighttime cars
    }
    glPopMatrix();
}

void vehicle()
{
    moveCarLeft();  // Handle left-moving cars
    moveCarRight(); // Handle right-moving cars
}

void moveCloud()
{

    if (moveCloudRight)
    {
        CloudX += 0.3;  // cloud speed to the right
    }

    if (CloudX > 1200)
    {
        CloudX = -1200; // Reset position when the cloud goes out of the screen
    }

    glPushMatrix();
    glTranslatef(CloudX, CloudY, 0);
    if (isDay)
    {
        DayCloud();
    }
    else
    {
        NightCloud();
    }
    glPopMatrix();
}
void sunRise()

{
    if (!sunSitThere) /// untill sun stop
    {
        sunY += .3;   /// speed
    }
    if (sunY > 290)   /// sun stop position
    {
        text(10, 540, "Press N to make Night");
        sunSitThere = true;
    }
    glPushMatrix();
    glTranslatef(sunX, sunY, 0);
    sun();
    glPopMatrix();
}
void sunset()

{

    if (makeItNight)
    {
        sunY -= .3;   /// - coz down to y
    }
    if (sunY < -125) /// pushing sun downwerd
    {
        isDay = false;
        sunY = 0;
    }

    glPushMatrix();
    glTranslatef(sunX, sunY, 0);
    sun();
    glPopMatrix();
}
void MoonRise()

{
    if (!moonSitThere) /// untill moon stop
    {
        moonY += .3;   ///  moon speed  up to y exis
    }
    if (moonY > 290)  /// stop here
    {
        text(10, 540, "Press D to make Day");
        moonSitThere = true;
    }
    glPushMatrix();
    glTranslatef(moonX, moonY, 0);
    moon();
    glPopMatrix();
}
void moonset()

{

    if (makeItDay)
    {
        moonY -= .3;
    }
    if (moonY < -100)
    {
        isDay = true;
        moonY = 0;
    }

    glPushMatrix();
    glTranslatef(moonX, moonY, 0);
    moon();
    glPopMatrix();
}
void BgBuildingDayTime()
{
    ///bg building 1 shado

   glVertex2i(174, 360);
    glVertex2i(174, 340);
    glEnd();

    glColor3ub(195, 203, 200); //top
    glBegin(GL_QUADS);
    glVertex2i(138, 284);
    glVertex2i(179, 284);
    glVertex2i(178, 342);
    glVertex2i(138, 340);
    glEnd();

    glColor3ub(195, 203, 200); //bottom
    glBegin(GL_QUADS);
    glVertex2i(124, 170);
    glVertex2i(179, 170);
    glVertex2i(179, 284);
    glVertex2i(124, 284);
    glEnd();

    glColor3ub(195, 203, 200); //right_side
    glBegin(GL_QUADS);
    glVertex2i(179, 170);
    glVertex2i(186, 170);
    glVertex2i(186, 276);
    glVertex2i(179, 284);
    glEnd();

    glColor3ub(151, 163, 151); //bottom_shadow
    glBegin(GL_QUADS);
    glVertex2i(115, 170);
    glVertex2i(124, 170);
    glVertex2i(124, 284);
    glVertex2i(115, 284);
    glEnd();

    glColor3ub(151, 163, 151); //top_shadow
    glBegin(GL_QUADS);
    glVertex2i(129, 284);
    glVertex2i(138, 284);
    glVertex2i(138, 342);
    glVertex2i(129, 340);
    glEnd();
    ///end


    ///BG Building 2 shado


    glColor3ub(195, 203, 200); //top
    glBegin(GL_QUADS);
    glVertex2i(354, 170);
    glVertex2i(397, 170);
    glVertex2i(397, 380);
    glVertex2i(354, 380);
    glEnd();

    glColor3ub(151, 163, 151); //top_shadow
    glBegin(GL_QUADS);
    glVertex2i(344, 170);
    glVertex2i(354, 170);
    glVertex2i(354, 380);
    glVertex2i(344, 380);
    glEnd();

    glColor3ub(195, 203, 200); //right
    glBegin(GL_QUADS);
    glVertex2i(401, 340);
    glVertex2i(397, 340);
    glVertex2i(397, 372);
    glVertex2i(401, 369);
    glEnd();
    glColor3ub(195, 203, 200); //right_2
    glBegin(GL_QUADS);
    glVertex2i(408, 170);
    glVertex2i(397, 170);
    glVertex2i(397, 353);
    glVertex2i(408, 345);
    glEnd();
    ///end*/

    ///BG Building 3 shado
   glColor3ub(195, 203, 200); //top_1
    glBegin(GL_QUADS);
    glVertex2i(461, 400);
    glVertex2i(484, 400);
    glVertex2i(484, 387);
    glVertex2i(461, 387);
    glEnd();

    glColor3ub(151, 163, 151); //top_1_shadow
    glBegin(GL_QUADS);
    glVertex2i(451, 398);
    glVertex2i(461, 398);
    glVertex2i(461, 387);
    glVertex2i(451, 387);
    glEnd();

    glColor3ub(151, 163, 151); //top_2_curve_shadow
    glBegin(GL_QUADS);
    glVertex2i(451, 387);
    glVertex2i(474, 387);
    glVertex2i(474, 380);
    glVertex2i(448, 380);
    glEnd();

    glColor3ub(195, 203, 200); //top_2_curve
    glBegin(GL_QUADS);
    glVertex2i(461, 387);
    glVertex2i(484, 387);
    glVertex2i(487, 380);
    glVertex2i(458, 380);
    glEnd();

    glColor3ub(151, 163, 151); //top_2_shadow
    glBegin(GL_QUADS);
    glVertex2i(448, 380);
    glVertex2i(477, 380);
    glVertex2i(477, 350);
    glVertex2i(448, 350);
    glEnd();

    glColor3ub(195, 203, 200); //top_2
    glBegin(GL_QUADS);
    glVertex2i(458, 380);
    glVertex2i(487, 380);
    glVertex2i(487, 350);
    glVertex2i(458, 350);
    glEnd();

    glColor3ub(151, 163, 151); //top_curve
    glBegin(GL_QUADS);
    glVertex2i(445, 343);
    glVertex2i(480, 343);
    glVertex2i(477, 350);
    glVertex2i(448, 350);
    glEnd();

    glColor3ub(195, 203, 200); //top_curve
    glBegin(GL_QUADS);
    glVertex2i(455, 343);
    glVertex2i(490, 343);
    glVertex2i(487, 350);
    glVertex2i(458, 350);
    glEnd();

    glColor3ub(151, 163, 151); //main_shadow
    glBegin(GL_QUADS);
    glVertex2i(445, 170);
    glVertex2i(480, 170);
    glVertex2i(480, 343);
    glVertex2i(445, 343);
    glEnd();

    glColor3ub(195, 203, 200); //main
    glBegin(GL_QUADS);
    glVertex2i(455, 170);
    glVertex2i(490, 170);
    glVertex2i(490, 343);
    glVertex2i(455, 343);
    glEnd();

    glColor3ub(195, 203, 200); //righty
    glBegin(GL_QUADS);
    glVertex2i(490, 170);
    glVertex2i(513, 170);
    glVertex2i(513, 319);
    glVertex2i(490, 319);
    glEnd();

    ///end

    ///BG Building 4 shado
    glColor3ub(195, 203, 200); //top_stick!
    glBegin(GL_LINES);
    glLineWidth(2);
    glVertex2i(760, 380);
    glVertex2i(760, 346);
    glEnd();

    glColor3ub(195, 203, 200); //top_1
    glBegin(GL_QUADS);
    glVertex2i(748, 346);
    glVertex2i(762, 346);
    glVertex2i(762, 361);
    glVertex2i(748, 361);
    glEnd();

    glColor3ub(195, 203, 200); //top_2
    glBegin(GL_QUADS);
    glVertex2i(730, 340);
    glVertex2i(764, 340);
    glVertex2i(764, 346);
    glVertex2i(730, 346);
    glEnd();

    glColor3ub(195, 203, 200); //main
    glBegin(GL_QUADS);
    glVertex2i(723, 170);
    glVertex2i(762, 170);
    glVertex2i(762, 340);
    glVertex2i(723, 340);
    glEnd();

    glColor3ub(195, 203, 200); //right
    glBegin(GL_QUADS);
    glVertex2i(762, 170);
    glVertex2i(768, 170);
    glVertex2i(768, 345);
    glVertex2i(762, 350);
    glEnd();
    ///end


    ///BG Building 5 shado
    glColor3ub(195, 203, 200); //main_curve
    glBegin(GL_QUADS);
    glVertex2i(945, 347);
    glVertex2i(990, 347);
    glVertex2i(985, 350);
    glVertex2i(949, 350);
    glEnd();

    glColor3ub(195, 203, 200); //main
    glBegin(GL_QUADS);
    glVertex2i(945, 170);
    glVertex2i(990, 170);
    glVertex2i(990, 347);
    glVertex2i(945, 347);
    glEnd();

    glColor3ub(195, 203, 200); //left
    glBegin(GL_QUADS);
    glVertex2i(942, 170);
    glVertex2i(945, 170);
    glVertex2i(945, 274);
    glVertex2i(942, 271);
    glEnd();

    glColor3ub(195, 203, 200); //right
    glBegin(GL_QUADS);
    glVertex2i(990, 170);
    glVertex2i(996, 170);
    glVertex2i(996, 285);
    glVertex2i(990, 290);
    glEnd();

    glColor3ub(195, 203, 200); //right_2
    glBegin(GL_QUADS);
    glVertex2i(996, 170);
    glVertex2i(1008, 170);
    glVertex2i(1008, 255);
    glVertex2i(996, 255);
    glEnd();
    ///end


    ///Middle Building  tall
    glColor3ub(148, 179, 163); //main
    glBegin(GL_QUADS);
    glVertex2i(580, 170);
    glVertex2i(619, 170);
    glVertex2i(619, 344);
    glVertex2i(580, 344);
    glEnd();

    glColor3ub(117, 152, 135); //right_side
    glBegin(GL_QUADS);
    glVertex2i(619, 170);
    glVertex2i(629, 170);
    glVertex2i(629, 344);
    glVertex2i(619, 344);
    glEnd();

   glColor3ub(255, 255, 255); //main_window_white
    glBegin(GL_QUADS);
    glVertex2i(585, 221);
    glVertex2i(615, 221);
    glVertex2i(615, 340);
    glVertex2i(585, 340);
    glEnd();

   glColor3ub(148, 179, 163);
    glBegin(GL_LINES); ///1V vertical
    glVertex2i(592, 340);
    glVertex2i(592, 174);
    glEnd();

    glBegin(GL_LINES); //2V
    glVertex2i(600, 340);
    glVertex2i(600, 174);
    glEnd();

    glBegin(GL_LINES); //3V
    glVertex2i(608, 340);
    glVertex2i(608, 174);
    glEnd();

    glBegin(GL_LINES); ///H1 horizontal
    glVertex2i(585, 323);
    glVertex2i(615, 323);
    glEnd();

    glBegin(GL_LINES); //H2
    glVertex2i(585, 306);
    glVertex2i(615, 306);
    glEnd();

    glBegin(GL_LINES); //H3
    glVertex2i(585, 289);
    glVertex2i(615, 289);
    glEnd();

    glBegin(GL_LINES); //H4
    glVertex2i(585, 272);
    glVertex2i(615, 272);
    glEnd();

    glBegin(GL_LINES); //H5
    glVertex2i(585, 255);
    glVertex2i(615, 255);
    glEnd();

    glBegin(GL_LINES); //H6
    glVertex2i(585, 238);
    glVertex2i(615, 238);
    glEnd();

    glBegin(GL_LINES); //H7
    glVertex2i(585, 221);
    glVertex2i(615, 221);
    glEnd();

    ///end

}

void BgBuildingNightTime()
{
  ///bg building 1 shado
    glColor3ub(0, 114, 158);
    //top_stick!
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2i(164, 350);
    glVertex2i(164, 340);

    glVertex2i(174, 360);
    glVertex2i(174, 340);
    glEnd();

    //top
    glBegin(GL_QUADS);
    glVertex2i(138, 284);
    glVertex2i(179, 284);
    glVertex2i(178, 342);
    glVertex2i(138, 340);
    glEnd();

    //bottom
    glBegin(GL_QUADS);
    glVertex2i(124, 170);
    glVertex2i(179, 170);
    glVertex2i(179, 284);
    glVertex2i(124, 284);
    glEnd();

    //right_side
    glBegin(GL_QUADS);
    glVertex2i(179, 170);
    glVertex2i(186, 170);
    glVertex2i(186, 276);
    glVertex2i(179, 284);
    glEnd();

    ///BG Building 2
    glColor3ub(0, 114, 158);
    //top_quad
    glBegin(GL_QUADS);
    glVertex2i(374, 380);
    glVertex2i(397, 380);
    glVertex2i(397, 401);
    glVertex2i(374, 411);
    glEnd();

    //top
    glBegin(GL_QUADS);
    glVertex2i(354, 170);
    glVertex2i(397, 170);
    glVertex2i(397, 380);
    glVertex2i(354, 380);
    glEnd();

    //right_B3
    glBegin(GL_QUADS);
    glVertex2i(336, 170);
    glVertex2i(349, 170);
    glVertex2i(349, 270);
    glVertex2i(336, 270);
    glEnd();

    //right
    glBegin(GL_QUADS);
    glVertex2i(401, 340);
    glVertex2i(397, 340);
    glVertex2i(397, 372);
    glVertex2i(401, 369);
    glEnd();

    //right_2
    glBegin(GL_QUADS);
    glVertex2i(408, 170);
    glVertex2i(397, 170);
    glVertex2i(397, 353);
    glVertex2i(408, 345);
    glEnd();
    ///end

    ///BG Building 3
    glColor3ub(0, 91, 133);
    //top_1
    glBegin(GL_QUADS);
    glVertex2i(461, 400);
    glVertex2i(484, 400);
    glVertex2i(484, 387);
    glVertex2i(461, 387);
    glEnd();

    //top_2_curve
    glBegin(GL_QUADS);
    glVertex2i(461, 387);
    glVertex2i(484, 387);
    glVertex2i(487, 380);
    glVertex2i(458, 380);
    glEnd();

    //top_2
    glBegin(GL_QUADS);
    glVertex2i(458, 380);
    glVertex2i(487, 380);
    glVertex2i(487, 350);
    glVertex2i(458, 350);
    glEnd();

    //top_curve
    glBegin(GL_QUADS);
    glVertex2i(455, 343);
    glVertex2i(490, 343);
    glVertex2i(487, 350);
    glVertex2i(458, 350);
    glEnd();

    //main
    glBegin(GL_QUADS);
    glVertex2i(455, 170);
    glVertex2i(490, 170);
    glVertex2i(490, 343);
    glVertex2i(455, 343);
    glEnd();

    //righty
    glBegin(GL_QUADS);
    glVertex2i(490, 170);
    glVertex2i(513, 170);
    glVertex2i(513, 319);
    glVertex2i(490, 319);
    glEnd();

    ///end

    ///BG Building 4  shado
    glColor3ub(0, 114, 158); //main_curve
    glBegin(GL_QUADS);
    glVertex2i(945, 347);
    glVertex2i(990, 347);
    glVertex2i(985, 350);
    glVertex2i(949, 350);
    glEnd();

    //main
    glBegin(GL_QUADS);
    glVertex2i(945, 170);
    glVertex2i(990, 170);
    glVertex2i(990, 347);
    glVertex2i(945, 347);
    glEnd();

    //left
    glBegin(GL_QUADS);
    glVertex2i(942, 170);
    glVertex2i(945, 170);
    glVertex2i(945, 274);
    glVertex2i(942, 271);
    glEnd();

    //right
    glBegin(GL_QUADS);
    glVertex2i(990, 170);
    glVertex2i(996, 170);
    glVertex2i(996, 285);
    glVertex2i(990, 290);
    glEnd();

    //right_2
    glBegin(GL_QUADS);
    glVertex2i(996, 170);
    glVertex2i(1008, 170);
    glVertex2i(1008, 255);
    glVertex2i(996, 255);
    glEnd();
    ///end

    ///BG Building 5 shado
    glColor3ub(0, 114, 158); //main_curve
    glBegin(GL_QUADS);
    glVertex2i(1060, 300);
    glVertex2i(1110, 300);
    glVertex2i(1105, 305);
    glVertex2i(1065, 305);
    glEnd();

    //main
    glBegin(GL_QUADS);
    glVertex2i(1060, 170);
    glVertex2i(1110, 170);
    glVertex2i(1110, 300);
    glVertex2i(1060, 300);
    glEnd();
    ///end

}

struct Tree
{
    void drawdayTree() // for day
    {
        glColor3ub(78,148,45); ///green leaf 1
        glBegin(GL_TRIANGLES);
        glVertex2i(370,250);
        glVertex2i(440,255);
        glVertex2i(400,290);
        glEnd();

        glColor3ub(39,118,37); //2
        glBegin(GL_TRIANGLES);
        glVertex2i(375,272);
        glVertex2i(432,268);
        glVertex2i(405,297);
        glEnd();

        glColor3ub(78,148,45); //3
        glBegin(GL_TRIANGLES);
        glVertex2i(380,290);
        glVertex2i(425,290);
        glVertex2i(405,315);
        glEnd();

        glColor3ub(119,68,34);/// tree body
        glBegin(GL_QUADS);
        glVertex2i(400,235);
        glVertex2i(410,235);
        glVertex2i(410,253);
        glVertex2i(400,253);
        glEnd();

    }

    void drawnightTree() //for night
    {
        glColor3ub(26,77,132); /// green leaf 1
        glBegin(GL_TRIANGLES);
        glVertex2i(370,250);
        glVertex2i(440,255);
        glVertex2i(400,290);
        glEnd();

        glColor3ub(26,77,132); //2
        glBegin(GL_TRIANGLES);
        glVertex2i(375,272);
        glVertex2i(432,268);
        glVertex2i(405,297);
        glEnd();

        glColor3ub(26,77,132); //3
        glBegin(GL_TRIANGLES);
        glVertex2i(380,290);
        glVertex2i(425,290);
        glVertex2i(405,315);
        glEnd();

        glColor3ub(26,77,132); //4
        glBegin(GL_QUADS);
        glVertex2i(400,235);
        glVertex2i(410,235);
        glVertex2i(410,253);
        glVertex2i(400,253);
        glEnd();

        glPointSize(2); /// pixel size     ///tree lighting
        glColor3ub(255,255,0);
        glBegin(GL_POINTS);
        glVertex2i(394,300);
        glVertex2i(406,297);
        glVertex2i(386,287);
        glVertex2i(396,271);
        glVertex2i(426,261);
        glVertex2i(415,279);
        glVertex2i(400,279);
        glVertex2i(380,255);
        glEnd();
    }
};

void dayTree()
{
    Tree t;
    glPushMatrix();
    glTranslated(-100, -100, 0); /// copy tree 1 positon
    t.drawdayTree();
    glPopMatrix();

    glPushMatrix();/// 2
    glTranslated(60, -95, 0);
    t.drawdayTree();
    glPopMatrix();

    glPushMatrix();///3
    glTranslated(80, -95, 0);
    t.drawdayTree();
    glPopMatrix();

    glPushMatrix();///4
    glTranslated(170, -110, 0);
    t.drawdayTree();
    glPopMatrix();

    glPushMatrix();///5
    glTranslated(270, -100, 0);
    t.drawdayTree();
    glPopMatrix();

    glPushMatrix();///6
    glTranslated(-300, -110, 0);
    t.drawdayTree();
    glPopMatrix();

    glPushMatrix();///7
    glTranslated(380, -100, 0);
    t.drawdayTree();
    glPopMatrix();

    glPushMatrix();///8
    glTranslated(400, -110, 0);
    t.drawdayTree();
    glPopMatrix();

    glPushMatrix();///9
    glTranslated(600, -100, 0);
    t.drawdayTree();
    glPopMatrix();

}

void nightTree()
{

    Tree t;
    glPushMatrix();
    glTranslated(-100, -100, 0); /// copy tree 1 positon
    t.drawnightTree();
    glPopMatrix();

    glPushMatrix();
    glTranslated(60, -95, 0);///1
    t.drawnightTree();
    glPopMatrix();

    glPushMatrix();///2
    glTranslated(80, -95, 0);
    t.drawnightTree();
    glPopMatrix();

    glPushMatrix();///3
    glTranslated(170, -110, 0);
    t.drawnightTree();
    glPopMatrix();

    glPushMatrix();///4
    glTranslated(270, -100, 0);
    t.drawnightTree();
    glPopMatrix();

    glPushMatrix();///5
    glTranslated(-300, -110, 0);
    t.drawnightTree();
    glPopMatrix();

    glPushMatrix();///6
    glTranslated(380, -100, 0);
    t.drawnightTree();
    glPopMatrix();

    glPushMatrix();///7
    glTranslated(400, -110, 0);
    t.drawnightTree();
    glPopMatrix();

    glPushMatrix();///8
    glTranslated(600, -100, 0);
    t.drawnightTree();
    glPopMatrix();
}
void wheel(int x, int y, int outer, int inner) /// wheel
{
    glPushMatrix();
    glColor3ub(0, 22, 51); /// wheel out colour
    DrawCircle(x, y, outer, 2000); ///outer circle, radius=2000
    glColor3ub(164, 199, 178);/// inner whell colour
    DrawCircle(x, y, inner, 2000);
    glPopMatrix();
}

void RoadFieldDay()
{
    ///Green Field
    glColor3ub(169, 188, 60);
    glBegin(GL_QUADS);
    glVertex2i(0, 170);
    glVertex2i(0, 122);
    glVertex2i(1200, 122);
    glVertex2i(1200, 170);
    glEnd();
    ///end

    ///Road
    glColor3ub(254, 206, 8);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(1200, 0);
    glVertex2i(1200, 122);
    glVertex2i(0, 122);
    glEnd();

    glPushAttrib(GL_ENABLE_BIT);
    glLineWidth(5); /// road_strip wide
    glLineStipple(10, 0xAAAA);///hexa decimal
    glEnable(GL_LINE_STIPPLE);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2i(0, 58);
    glVertex2i(1190, 58);
    glEnd();
    glPopAttrib();

    ///end
}
void RoadFielNight()
{
    ///Green Field
    glColor3ub(9, 27, 32);
    glBegin(GL_QUADS);
    glVertex2i(0, 170);
    glVertex2i(0, 122);
    glVertex2i(1200, 122);
    glVertex2i(1200, 170);
    glEnd();
    ///end

    ///Road
    glColor3ub(27, 66, 121);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(1200, 0);
    glVertex2i(1200, 122);
    glVertex2i(0, 122);
    glEnd();

    glPushAttrib(GL_ENABLE_BIT);
    glLineWidth(5); // road_strip
    glLineStipple(10, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glColor3ub(6, 95, 138);
    glBegin(GL_LINES);
    glVertex2i(0, 58);
    glVertex2i(1190, 58);
    glEnd();
    glPopAttrib();

    ///end
}
void DayTime()
{

    //yellow building
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(251, 185, 23);
    glVertex2i(0, 145);
    glVertex2i(20, 145);
    glVertex2i(20, 260);
    glVertex2i(0, 260);
    glEnd();

    glBegin(GL_QUADS); //1st Building Top bar
    glColor3ub(65, 51, 0);
    glVertex2i(0, 260);
    glVertex2i(20, 260);
    glVertex2i(20, 266);
    glVertex2i(0, 266);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(245, 225, 164);
    glVertex2i(20, 145);
    glVertex2i(64, 145);
    glVertex2i(64, 260);
    glVertex2i(20, 260);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(65, 51, 0);
    glVertex2i(20, 260);
    glVertex2i(64, 260);
    glVertex2i(64, 266);
    glVertex2i(20, 266);
    glEnd();

    //window 1
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(25, 237);
    glVertex2i(33, 237);
    glVertex2i(33, 250);
    glVertex2i(25, 250);
    glEnd();

    //window 2
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(37, 237);
    glVertex2i(45, 237);
    glVertex2i(45, 250);
    glVertex2i(37, 250);
    glEnd();

    //window 3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(50, 237);
    glVertex2i(58, 237);
    glVertex2i(58, 250);
    glVertex2i(50, 250);
    glEnd();


    //window 4
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(25, 215);
    glVertex2i(33, 215);
    glVertex2i(33, 228);
    glVertex2i(25, 228);
    glEnd();

    //window 5

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(37, 215);
    glVertex2i(45, 215);
    glVertex2i(45, 228);
    glVertex2i(37, 228);
    glEnd();



    //window 6
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(50, 215);
    glVertex2i(58, 215);
    glVertex2i(58, 228);
    glVertex2i(50, 228);
    glEnd();

    //window 7
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(25, 195);
    glVertex2i(33, 195);
    glVertex2i(33, 208);
    glVertex2i(25, 208);
    glEnd();

    //window 8

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(37, 195);
    glVertex2i(45, 195);
    glVertex2i(45, 208);
    glVertex2i(37, 208);
    glEnd();

    //window 9

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 255, 252);
    glVertex2i(50, 195);
    glVertex2i(58, 195);
    glVertex2i(58, 208);
    glVertex2i(50, 208);
    glEnd();

    ///green building left 2

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(201, 78, 44);
    glVertex2i(90, 150);
    glVertex2i(100, 150);
    glVertex2i(100, 275);
    glVertex2i(90, 275);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(201, 78, 44);
    glVertex2i(85, 270);
    glVertex2i(95, 270);
    glVertex2i(95, 280);
    glVertex2i(85, 280);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(36, 71, 66);
    glVertex2i(100, 150);
    glVertex2i(160, 150);
    glVertex2i(160, 275);
    glVertex2i(100, 275);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(36, 71, 66);
    glVertex2i(90, 275);
    glVertex2i(165, 275);
    glVertex2i(165, 280);
    glVertex2i(90, 280);
    glEnd();

    //window 1
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(104, 245);
    glVertex2i(118, 245);
    glVertex2i(118, 265);
    glVertex2i(104, 265);
    glEnd();



    //window 2
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(124, 245);
    glVertex2i(138, 245);
    glVertex2i(138, 265);
    glVertex2i(124, 265);
    glEnd();

    //window 3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(142, 245);
    glVertex2i(156, 245);
    glVertex2i(156, 265);
    glVertex2i(142, 265);
    glEnd();


    //window 4
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(104, 215);
    glVertex2i(118, 215);
    glVertex2i(118, 235);
    glVertex2i(104, 235);
    glEnd();


    //window 5
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(124, 215);
    glVertex2i(138, 215);
    glVertex2i(138, 235);
    glVertex2i(124, 235);
    glEnd();


    //window 6
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(142, 215);
    glVertex2i(156, 215);
    glVertex2i(156, 235);
    glVertex2i(142, 235);
    glEnd();


    //window 7
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(104, 185);
    glVertex2i(118, 185);
    glVertex2i(118, 205);
    glVertex2i(104, 205);
    glEnd();

    //window 8
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(124, 185);
    glVertex2i(138, 185);
    glVertex2i(138, 205);
    glVertex2i(124, 205);
    glEnd();


    //window 9
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(142, 185);
    glVertex2i(156, 185);
    glVertex2i(156, 205);
    glVertex2i(142, 205);
    glEnd();


    ///red building left 3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(146, 44, 27);
    glVertex2i(228, 145);
    glVertex2i(237, 145);
    glVertex2i(237, 310);
    glVertex2i(228, 310);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(146, 44, 27);
    glVertex2i(227, 305);
    glVertex2i(232, 305);
    glVertex2i(232, 315);
    glVertex2i(227, 315);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(209, 70, 42);
    glVertex2i(237, 145);
    glVertex2i(300, 145);
    glVertex2i(300, 310);
    glVertex2i(237, 310);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(209, 70, 42);
    glVertex2i(232, 310);
    glVertex2i(305, 310);
    glVertex2i(305, 315);
    glVertex2i(232, 315);
    glEnd();

    //window 1

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(250, 270);
    glVertex2i(262, 270);
    glVertex2i(262, 295);
    glVertex2i(250, 295);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(250, 285);
    glVertex2i(262, 285);
    glVertex2i(256, 270);
    glVertex2i(256, 295);
    glEnd();
    //window 2

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(267, 270);
    glVertex2i(279, 270);
    glVertex2i(279, 295);
    glVertex2i(267, 295);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(267, 285);
    glVertex2i(279, 285);
    glVertex2i(273, 270);
    glVertex2i(273, 295);
    glEnd();

    //window 3

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(284, 270);
    glVertex2i(296, 270);
    glVertex2i(296, 295);
    glVertex2i(284, 295);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(284, 285);
    glVertex2i(296, 285);
    glVertex2i(290, 270);
    glVertex2i(290, 295);
    glEnd();

    //window 4

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(250, 235);
    glVertex2i(262, 235);
    glVertex2i(262, 260);
    glVertex2i(250, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(250, 250);
    glVertex2i(262, 250);
    glVertex2i(256, 235);
    glVertex2i(256, 260);
    glEnd();

    //window 5

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(267, 235);
    glVertex2i(279, 235);
    glVertex2i(279, 260);
    glVertex2i(267, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(267, 250);
    glVertex2i(279, 250);
    glVertex2i(273, 235);
    glVertex2i(273, 260);
    glEnd();

    //window 6

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(284, 235);
    glVertex2i(296, 235);
    glVertex2i(296, 260);
    glVertex2i(284, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(284, 250);
    glVertex2i(296, 250);
    glVertex2i(290, 235);
    glVertex2i(290, 260);
    glEnd();

    //window 7

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(250, 195);
    glVertex2i(262, 195);
    glVertex2i(262, 220);
    glVertex2i(250, 220);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(250, 210);
    glVertex2i(262, 210);
    glVertex2i(256, 195);
    glVertex2i(256, 220);
    glEnd();

    //window 8

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(267, 195);
    glVertex2i(279, 195);
    glVertex2i(279, 220);
    glVertex2i(267, 220);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(267, 210);
    glVertex2i(279, 210);
    glVertex2i(273, 195);
    glVertex2i(273, 220);
    glEnd();

    //window 9

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(131, 180, 160);
    glVertex2i(284, 195);
    glVertex2i(296, 195);
    glVertex2i(296, 220);
    glVertex2i(284, 220);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(104, 135, 118);
    glVertex2i(284, 210);
    glVertex2i(296, 210);
    glVertex2i(290, 195);
    glVertex2i(290, 220);
    glEnd();

    /// 4th building left

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(145, 55, 50);
    glVertex2i(405, 145);
    glVertex2i(430, 145);
    glVertex2i(430, 330);
    glVertex2i(405, 330);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(247, 165, 63);
    glVertex2i(430, 145);
    glVertex2i(485, 145);
    glVertex2i(485, 330);
    glVertex2i(430, 330);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(16, 17, 8);
    glVertex2i(405, 330);
    glVertex2i(430, 330);
    glVertex2i(430, 336);
    glVertex2i(405, 336);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(241, 205, 54);
    glVertex2i(430, 330);
    glVertex2i(485, 330);
    glVertex2i(485, 336);
    glVertex2i(430, 336);
    glEnd();

    glBegin(GL_QUADS); ///1st window
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(436, 305);
    glVertex2i(446, 305);
    glVertex2i(446, 315);
    glVertex2i(436, 315);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(436, 316);
    glVertex2i(446, 316);
    glVertex2i(446, 318);
    glVertex2i(436, 318);
    glEnd();

    glBegin(GL_QUADS); ///2nd
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(450, 305);
    glVertex2i(460, 305);
    glVertex2i(460, 315);
    glVertex2i(450, 315);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(450, 316);
    glVertex2i(460, 316);
    glVertex2i(460, 318);
    glVertex2i(450, 318);
    glEnd();

    glBegin(GL_QUADS); ///3rd
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(465, 305);
    glVertex2i(475, 305);
    glVertex2i(475, 315);
    glVertex2i(465, 315);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(465, 316);
    glVertex2i(475, 316);
    glVertex2i(475, 318);
    glVertex2i(465, 318);
    glEnd();

    glBegin(GL_QUADS); ///1st bar
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 299);
    glVertex2i(475, 299);
    glVertex2i(475, 302);
    glVertex2i(435, 302);
    glEnd();

    glBegin(GL_QUADS); ///4th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(435, 265);
    glVertex2i(445, 265);
    glVertex2i(445, 275);
    glVertex2i(435, 275);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 275);
    glVertex2i(445, 275);
    glVertex2i(445, 277);
    glVertex2i(435, 277);
    glEnd();

    glBegin(GL_QUADS); ///5th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(465, 265);
    glVertex2i(475, 265);
    glVertex2i(475, 275);
    glVertex2i(465, 275);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(465, 275);
    glVertex2i(475, 275);
    glVertex2i(475, 277);
    glVertex2i(465, 277);
    glEnd();

    glBegin(GL_QUADS); ///6th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(450, 265);
    glVertex2i(460, 265);
    glVertex2i(460, 275);
    glVertex2i(450, 275);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(450, 275);
    glVertex2i(460, 275);
    glVertex2i(460, 277);
    glVertex2i(450, 277);
    glEnd();

    glBegin(GL_QUADS); ///2nd bar
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 262);
    glVertex2i(475, 262);
    glVertex2i(475, 259);
    glVertex2i(435, 259);
    glEnd();

    glBegin(GL_QUADS); ///7th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(435, 220);
    glVertex2i(445, 220);
    glVertex2i(445, 230);
    glVertex2i(435, 230);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 231);
    glVertex2i(445, 231);
    glVertex2i(445, 233);
    glVertex2i(435, 233);
    glEnd();

    glBegin(GL_QUADS); ///8th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(450, 220);
    glVertex2i(460, 220);
    glVertex2i(460, 230);
    glVertex2i(450, 230);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(450, 231);
    glVertex2i(460, 231);
    glVertex2i(460, 233);
    glVertex2i(450, 233);
    glEnd();

    glBegin(GL_QUADS); ///9th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(465, 220);
    glVertex2i(475, 220);
    glVertex2i(475, 230);
    glVertex2i(465, 230);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(465, 231);
    glVertex2i(475, 231);
    glVertex2i(475, 233);
    glVertex2i(465, 233);
    glEnd();

    glBegin(GL_QUADS); ///3rd bar
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 214);
    glVertex2i(475, 214);
    glVertex2i(475, 217);
    glVertex2i(435, 217);
    glEnd();

    glBegin(GL_QUADS); ///10th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(465, 175);
    glVertex2i(475, 175);
    glVertex2i(475, 185);
    glVertex2i(465, 185);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(465, 186);
    glVertex2i(475, 186);
    glVertex2i(475, 188);
    glVertex2i(465, 188);
    glEnd();

    glBegin(GL_QUADS); ///11th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(435, 175);
    glVertex2i(445, 175);
    glVertex2i(445, 185);
    glVertex2i(435, 185);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 186);
    glVertex2i(445, 186);
    glVertex2i(445, 188);
    glVertex2i(435, 188);
    glEnd();

    glBegin(GL_QUADS); ///12th
    glPointSize(10.0);
    glColor3ub(255, 253, 241);
    glVertex2i(450, 175);
    glVertex2i(460, 175);
    glVertex2i(460, 185);
    glVertex2i(450, 185);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(450, 186);
    glVertex2i(460, 186);
    glVertex2i(460, 188);
    glVertex2i(450, 188);
    glEnd();

    glBegin(GL_QUADS); ///last bar
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 170);
    glVertex2i(475, 170);
    glVertex2i(475, 173);
    glVertex2i(435, 173);
    glEnd();

    ///5th building left short yellow

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(254, 207, 7);
    glVertex2i(590, 145);
    glVertex2i(635, 145);
    glVertex2i(635, 200);
    glVertex2i(590, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(245, 225, 164);
    glVertex2i(635, 145);
    glVertex2i(685, 145);
    glVertex2i(685, 200);
    glVertex2i(635, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(254, 207, 7);
    glVertex2i(590, 145);
    glVertex2i(635, 145);
    glVertex2i(635, 200);
    glVertex2i(590, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(245, 225, 164);
    glVertex2i(635, 145);
    glVertex2i(685, 145);
    glVertex2i(685, 200);
    glVertex2i(635, 200);
    glEnd();

    //window 1
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(595, 190);
    glVertex2i(600, 190);
    glVertex2i(600, 185);
    glVertex2i(595, 185);
    glEnd();

    //window 2
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(602, 190);
    glVertex2i(607, 190);
    glVertex2i(607, 185);
    glVertex2i(602, 185);
    glEnd();

    //window 3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(609, 190);
    glVertex2i(614, 190);
    glVertex2i(614, 185);
    glVertex2i(609, 185);
    glEnd();

    //window 4
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(616, 190);
    glVertex2i(621, 190);
    glVertex2i(621, 185);
    glVertex2i(616, 185);
    glEnd();

    //window 5
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(623, 190);
    glVertex2i(628, 190);
    glVertex2i(628, 185);
    glVertex2i(623, 185);
    glEnd();

    //window 6
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(595, 175);
    glVertex2i(600, 175);
    glVertex2i(600, 180);
    glVertex2i(595, 180);
    glEnd();

    //window 7
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(602, 175);
    glVertex2i(607, 175);
    glVertex2i(607, 180);
    glVertex2i(602, 180);
    glEnd();

    //window 8
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(609, 175);
    glVertex2i(614, 175);
    glVertex2i(614, 180);
    glVertex2i(609, 180);
    glEnd();

    //window 9
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(616, 175);
    glVertex2i(621, 175);
    glVertex2i(621, 180);
    glVertex2i(616, 180);
    glEnd();

    //window 10
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(623, 175);
    glVertex2i(628, 175);
    glVertex2i(628, 180);
    glVertex2i(623, 180);
    glEnd();

    //window 11
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(595, 165);
    glVertex2i(600, 165);
    glVertex2i(600, 170);
    glVertex2i(595, 170);
    glEnd();

    //window 12
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(602, 165);
    glVertex2i(607, 165);
    glVertex2i(607, 170);
    glVertex2i(602, 170);
    glEnd();

    //window 13
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(609, 165);
    glVertex2i(614, 165);
    glVertex2i(614, 170);
    glVertex2i(609, 170);
    glEnd();

    //window 14
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(616, 165);
    glVertex2i(621, 165);
    glVertex2i(621, 170);
    glVertex2i(616, 170);
    glEnd();

    //window 15
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(623, 165);
    glVertex2i(628, 165);
    glVertex2i(628, 170);
    glVertex2i(623, 170);
    glEnd();

    //window 16
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(595, 155);
    glVertex2i(600, 155);
    glVertex2i(600, 160);
    glVertex2i(595, 160);
    glEnd();

    //window 17
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(602, 155);
    glVertex2i(607, 155);
    glVertex2i(607, 160);
    glVertex2i(602, 160);
    glEnd();

    //window 18
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(609, 155);
    glVertex2i(614, 155);
    glVertex2i(614, 160);
    glVertex2i(609, 160);
    glEnd();

    //window 19
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(616, 155);
    glVertex2i(621, 155);
    glVertex2i(621, 160);
    glVertex2i(616, 160);
    glEnd();

    //window 20
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 251, 254);
    glVertex2i(623, 155);
    glVertex2i(628, 155);
    glVertex2i(628, 160);
    glVertex2i(623, 160);
    glEnd();

    ///7th building left red

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(245, 94, 55);
    glVertex2i(705, 145);
    glVertex2i(765, 145);
    glVertex2i(765, 270);
    glVertex2i(705, 270);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(58, 81, 76);
    glVertex2i(695, 145);
    glVertex2i(705, 145);
    glVertex2i(705, 270);
    glVertex2i(695, 270);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(720, 250);
    glVertex2i(730, 250);
    glVertex2i(730, 260);
    glVertex2i(720, 260);
    glEnd();


    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(733, 250);
    glVertex2i(743, 250);
    glVertex2i(743, 260);
    glVertex2i(733, 260);
    glEnd();



    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(745, 250);
    glVertex2i(755, 250);
    glVertex2i(755, 260);
    glVertex2i(745, 260);
    glEnd();


    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(720, 235);
    glVertex2i(730, 235);
    glVertex2i(730, 245);
    glVertex2i(720, 245);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(720, 220);
    glVertex2i(730, 220);
    glVertex2i(730, 230);
    glVertex2i(720, 230);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(720, 205);
    glVertex2i(730, 205);
    glVertex2i(730, 215);
    glVertex2i(720, 215);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(720, 190);
    glVertex2i(730, 190);
    glVertex2i(730, 200);
    glVertex2i(720, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(720, 175);
    glVertex2i(730, 175);
    glVertex2i(730, 185);
    glVertex2i(720, 185);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(720, 160);
    glVertex2i(730, 160);
    glVertex2i(730, 170);
    glVertex2i(720, 170);
    glEnd();

    //2nd
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(733, 235);
    glVertex2i(743, 235);
    glVertex2i(743, 245);
    glVertex2i(733, 245);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(733, 220);
    glVertex2i(743, 220);
    glVertex2i(743, 230);
    glVertex2i(733, 230);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(733, 205);
    glVertex2i(743, 205);
    glVertex2i(743, 215);
    glVertex2i(733, 215);
    glEnd();


    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(733, 190);
    glVertex2i(743, 190);
    glVertex2i(743, 200);
    glVertex2i(733, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(733, 175);
    glVertex2i(743, 175);
    glVertex2i(743, 185);
    glVertex2i(733, 185);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(733, 160);
    glVertex2i(743, 160);
    glVertex2i(743, 170);
    glVertex2i(733, 170);
    glEnd();
    //3rd
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(745, 235);
    glVertex2i(755, 235);
    glVertex2i(755, 245);
    glVertex2i(745, 245);
    glEnd();



    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(745, 220);
    glVertex2i(755, 220);
    glVertex2i(755, 230);
    glVertex2i(745, 230);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(745, 205);
    glVertex2i(755, 205);
    glVertex2i(755, 215);
    glVertex2i(745, 215);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(745, 190);
    glVertex2i(755, 190);
    glVertex2i(755, 200);
    glVertex2i(745, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(745, 175);
    glVertex2i(755, 175);
    glVertex2i(755, 185);
    glVertex2i(745, 185);
    glEnd();



    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(157, 203, 178);
    glVertex2i(745, 160);
    glVertex2i(755, 160);
    glVertex2i(755, 170);
    glVertex2i(745, 170);
    glEnd();


    ///3rd building right blue
    glBegin(GL_QUADS); //red1 b2
    glPointSize(10.0);
    glColor3ub(208, 75, 36);
    glVertex2i(855, 155);
    glVertex2i(865, 155);
    glVertex2i(865, 330);
    glVertex2i(855, 330);
    glEnd();

    glBegin(GL_QUADS); //red2 b2 border
    glPointSize(10.0);
    glColor3ub(208, 75, 36);
    glVertex2i(850, 325);
    glVertex2i(865, 325);
    glVertex2i(865, 335);
    glVertex2i(850, 335);
    glEnd();
    glBegin(GL_QUADS); //green1 b2
    glPointSize(10.0);
    glColor3ub(29, 68, 59);
    glVertex2i(865, 155);
    glVertex2i(925, 155);
    glVertex2i(925, 330);
    glVertex2i(865, 330);
    glEnd();
    glBegin(GL_QUADS); //green2 b2 border
    glPointSize(10.0);
    glColor3ub(29, 68, 59);
    glVertex2i(860, 325);
    glVertex2i(930, 325);
    glVertex2i(930, 335);
    glVertex2i(860, 335);
    glEnd();
    glBegin(GL_QUADS); //w1 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(870, 290);
    glVertex2i(885, 290);
    glVertex2i(885, 310);
    glVertex2i(870, 310);
    glEnd();
    glBegin(GL_QUADS); //w2 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(890, 290);
    glVertex2i(905, 290);
    glVertex2i(905, 310);
    glVertex2i(890, 310);
    glEnd();
    glBegin(GL_QUADS); //w3 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(910, 290);
    glVertex2i(925, 290);
    glVertex2i(925, 310);
    glVertex2i(910, 310);
    glEnd();
    //line border1

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(184, 218, 194);
    glVertex2i(867, 282);
    glVertex2i(923, 282);
    glEnd();

    glBegin(GL_QUADS); //w4 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(870, 255);
    glVertex2i(885, 255);
    glVertex2i(885, 275);
    glVertex2i(870, 275);
    glEnd();
    glBegin(GL_QUADS); //w5 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(890, 255);
    glVertex2i(905, 255);
    glVertex2i(905, 275);
    glVertex2i(890, 275);
    glEnd();

    glBegin(GL_QUADS); //w6 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(910, 255);
    glVertex2i(925, 255);
    glVertex2i(925, 275);
    glVertex2i(910, 275);
    glEnd();
    //line border2
    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(184, 218, 194);
    glVertex2i(867, 244);
    glVertex2i(923, 244);
    glEnd();

    glBegin(GL_QUADS); //w7 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(870, 220);
    glVertex2i(885, 220);
    glVertex2i(885, 240);
    glVertex2i(870, 240);
    glEnd();

    glBegin(GL_QUADS); //w8 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(890, 220);
    glVertex2i(905, 220);
    glVertex2i(905, 240);
    glVertex2i(890, 240);
    glEnd();

    glBegin(GL_QUADS); //w9 b2
    glPointSize(10.0);
    glColor3ub(184, 218, 194);
    glVertex2i(910, 220);
    glVertex2i(925, 220);
    glVertex2i(925, 240);
    glVertex2i(910, 240);
    glEnd();

    //line border3
    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(184, 218, 194);
    glVertex2i(867, 204);
    glVertex2i(923, 204);
    glEnd();

    ///3rd building
    glBegin(GL_QUADS); //b3 border
    glPointSize(10.0);
    glColor3ub(82, 78, 55);
    glVertex2i(924, 145);
    glVertex2i(934, 145);
    glVertex2i(934, 252);
    glVertex2i(924, 252);
    glEnd();
    //Red part b3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(201, 79, 43);
    glVertex2i(934, 145);
    glVertex2i(995, 145);
    glVertex2i(995, 252);
    glVertex2i(934, 252);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w1 b3
    glVertex2i(952, 235);
    glVertex2i(960, 235);
    glVertex2i(960, 245);
    glVertex2i(952, 245);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w2 b3
    glVertex2i(975, 235);
    glVertex2i(984, 235);
    glVertex2i(984, 245);
    glVertex2i(975, 245);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w3 b3
    glVertex2i(940, 220);
    glVertex2i(950, 220);
    glVertex2i(950, 230);
    glVertex2i(940, 230);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w4 b3
    glVertex2i(963, 220);
    glVertex2i(973, 220);
    glVertex2i(973, 232);
    glVertex2i(963, 232);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w5 b3
    glVertex2i(952, 205);
    glVertex2i(960, 205);
    glVertex2i(960, 215);
    glVertex2i(952, 215);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w6 b3
    glVertex2i(975, 205);
    glVertex2i(984, 205);
    glVertex2i(984, 215);
    glVertex2i(975, 215);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w7 b3
    glVertex2i(940, 190);
    glVertex2i(950, 190);
    glVertex2i(950, 200);
    glVertex2i(940, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w8 b3
    glVertex2i(963, 190);
    glVertex2i(973, 190);
    glVertex2i(973, 200);
    glVertex2i(963, 200);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w9 b3
    glVertex2i(952, 180);
    glVertex2i(960, 180);
    glVertex2i(960, 190);
    glVertex2i(952, 190);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w10 b3
    glVertex2i(975, 180);
    glVertex2i(984, 180);
    glVertex2i(984, 190);
    glVertex2i(975, 190);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w11 b3
    glVertex2i(940, 165);
    glVertex2i(950, 165);
    glVertex2i(950, 175);
    glVertex2i(940, 175);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w12 b3
    glVertex2i(963, 165);
    glVertex2i(973, 165);
    glVertex2i(973, 175);
    glVertex2i(963, 175);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w13 b3
    glVertex2i(952, 150);
    glVertex2i(960, 150);
    glVertex2i(960, 160);
    glVertex2i(952, 160);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(198, 242, 237); //w14 b3
    glVertex2i(975, 150);
    glVertex2i(984, 150);
    glVertex2i(984, 160);
    glVertex2i(975, 160);
    glEnd();

    ///1st building right
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(241, 219, 168);
    glVertex2i(1010, 147);
    glVertex2i(1025, 147);
    glVertex2i(1025, 208);
    glVertex2i(1010, 208);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(191, 83, 22); //deep oranger part b4
    glVertex2i(1025, 147);
    glVertex2i(1030, 147);
    glVertex2i(1030, 208);
    glVertex2i(1025, 208);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(232, 107, 37); //light oranger part b4
    glVertex2i(1030, 147);
    glVertex2i(1060, 147);
    glVertex2i(1060, 208);
    glVertex2i(1030, 208);
    glEnd();
    glBegin(GL_QUADS); //light brik 1
    glPointSize(10.0);
    glColor3ub(241, 219, 168);
    glVertex2i(1060, 147);
    glVertex2i(1074, 147);
    glVertex2i(1074, 208);
    glVertex2i(1060, 208);
    glEnd();
    glBegin(GL_QUADS); //light brik 2
    glPointSize(10.0);
    glColor3ub(241, 219, 168);
    glVertex2i(1060, 147);
    glVertex2i(1074, 147);
    glVertex2i(1074, 208);
    glVertex2i(1060, 208);
    glEnd();
    glBegin(GL_QUADS); //light brik square
    glPointSize(10.0);
    glColor3ub(241, 219, 168);
    glVertex2i(1010, 208);
    glVertex2i(1074, 208);
    glVertex2i(1074, 233);
    glVertex2i(1010, 233);
    glEnd();
    glBegin(GL_QUADS); //white border
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1010, 233);
    glVertex2i(1074, 233);
    glVertex2i(1074, 239);
    glVertex2i(1010, 239);
    glEnd();
    glBegin(GL_QUADS); //upper brik
    glPointSize(10.0);
    glColor3ub(241, 219, 168);
    glVertex2i(1010, 239);
    glVertex2i(1074, 239);
    glVertex2i(1074, 282);
    glVertex2i(1010, 282);
    glEnd();
    glBegin(GL_QUADS); //W1
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1018, 260);
    glVertex2i(1024, 260);
    glVertex2i(1024, 270);
    glVertex2i(1018, 270);
    glEnd();
    glBegin(GL_QUADS); //W2
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1028, 260);
    glVertex2i(1035, 260);
    glVertex2i(1035, 270);
    glVertex2i(1028, 270);
    glEnd();
    glBegin(GL_QUADS); //W3
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1038, 260);
    glVertex2i(1045, 260);
    glVertex2i(1045, 270);
    glVertex2i(1038, 270);
    glEnd();
    glBegin(GL_QUADS); //W4
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1048, 260);
    glVertex2i(1055, 260);
    glVertex2i(1055, 270);
    glVertex2i(1048, 270);
    glEnd();
    glBegin(GL_QUADS); //W5
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1018, 249);
    glVertex2i(1024, 249);
    glVertex2i(1024, 258);
    glVertex2i(1018, 258);
    glEnd();
    glBegin(GL_QUADS); //W6
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1028, 249);
    glVertex2i(1035, 249);
    glVertex2i(1035, 258);
    glVertex2i(1028, 258);
    glEnd();
    glBegin(GL_QUADS); //W6
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1038, 249);
    glVertex2i(1045, 249);
    glVertex2i(1045, 258);
    glVertex2i(1038, 258);
    glEnd();
    glBegin(GL_QUADS); //W7
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1038, 249);
    glVertex2i(1045, 249);
    glVertex2i(1045, 258);
    glVertex2i(1038, 258);
    glEnd();
    glBegin(GL_QUADS); //W8
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1048, 249);
    glVertex2i(1055, 249);
    glVertex2i(1055, 258);
    glVertex2i(1048, 258);
    glEnd();
    //uppper triangle
    glBegin(GL_TRIANGLES);
    glPointSize(10.0);
    glColor3ub(121, 137, 109);
    glVertex2i(1010, 282);
    glVertex2i(1073, 282);
    glVertex2i(1053, 315);
    glEnd();
    glBegin(GL_QUADS); //deep border
    glPointSize(10.0);
    glColor3ub(44, 76, 63);
    glVertex2i(1010, 282);
    glVertex2i(1072, 282);
    glVertex2i(1072, 288);
    glVertex2i(1014, 288);
    glEnd();

    glBegin(GL_TRIANGLES);
    glPointSize(10.0);
    glColor3ub(56, 83, 58);
    glVertex2i(1073, 282);
    glVertex2i(1097, 282);
    glVertex2i(1053, 315);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(203, 175, 98);
    glVertex2i(1074, 147);
    glVertex2i(1097, 147);
    glVertex2i(1097, 282);
    glVertex2i(1074, 282);
    glEnd();
    glBegin(GL_QUADS); //w1
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1080, 262);
    glVertex2i(1085, 262);
    glVertex2i(1085, 273);
    glVertex2i(1080, 273);
    glEnd();
    glBegin(GL_QUADS); //w2
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1088, 263);
    glVertex2i(1093, 263);
    glVertex2i(1093, 273);
    glVertex2i(1088, 273);
    glEnd();
    glBegin(GL_QUADS); //w3
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1080, 249);
    glVertex2i(1085, 249);
    glVertex2i(1085, 258);
    glVertex2i(1080, 258);
    glEnd();
    glBegin(GL_QUADS); //w4
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1088, 249);
    glVertex2i(1093, 249);
    glVertex2i(1093, 258);
    glVertex2i(1088, 258);
    glEnd();
    glBegin(GL_QUADS); //w5
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1080, 232);
    glVertex2i(1085, 232);
    glVertex2i(1085, 244);
    glVertex2i(1080, 244);
    glEnd();
    glBegin(GL_QUADS); //w6
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1088, 232);
    glVertex2i(1093, 232);
    glVertex2i(1093, 244);
    glVertex2i(1088, 244);
    glEnd();

    glBegin(GL_QUADS); //w7
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1080, 216);
    glVertex2i(1085, 216);
    glVertex2i(1085, 228);
    glVertex2i(1080, 228);
    glEnd();
    glBegin(GL_QUADS); //w8
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1088, 216);
    glVertex2i(1093, 216);
    glVertex2i(1093, 228);
    glVertex2i(1088, 228);
    glEnd();
    glBegin(GL_QUADS); //w9
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1080, 204);
    glVertex2i(1085, 204);
    glVertex2i(1085, 213);
    glVertex2i(1080, 213);
    glEnd();
    glBegin(GL_QUADS); //w10
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1088, 204);
    glVertex2i(1093, 204);
    glVertex2i(1093, 213);
    glVertex2i(1088, 213);
    glEnd();
    glBegin(GL_QUADS); //w11
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1080, 188);
    glVertex2i(1085, 188);
    glVertex2i(1085, 198);
    glVertex2i(1080, 198);
    glEnd();
    glBegin(GL_QUADS); //w12
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1088, 188);
    glVertex2i(1093, 188);
    glVertex2i(1093, 198);
    glVertex2i(1088, 198);
    glEnd();

    glBegin(GL_QUADS); //w13
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1080, 173);
    glVertex2i(1085, 173);
    glVertex2i(1085, 182);
    glVertex2i(1080, 182);
    glEnd();
    glBegin(GL_QUADS); //w14
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1088, 173);
    glVertex2i(1093, 173);
    glVertex2i(1093, 182);
    glVertex2i(1088, 182);
    glEnd();
    glBegin(GL_QUADS); //w15
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1080, 157);
    glVertex2i(1085, 157);
    glVertex2i(1085, 169);
    glVertex2i(1080, 169);
    glEnd();
    glBegin(GL_QUADS); //w16
    glPointSize(10.0);
    glColor3ub(255, 255, 255);
    glVertex2i(1088, 157);
    glVertex2i(1093, 157);
    glVertex2i(1093, 169);
    glVertex2i(1088, 169);
    glEnd();

}
void NightTime()
{




   ///yellow building left 1
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(10, 44, 76);
    glVertex2i(0, 145);
    glVertex2i(20, 145);
    glVertex2i(20, 260);
    glVertex2i(0, 260);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(0, 12, 27);
    glVertex2i(0, 260);
    glVertex2i(20, 260);
    glVertex2i(20, 266);
    glVertex2i(0, 266);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(11, 132, 157);
    glVertex2i(20, 145);
    glVertex2i(64, 145);
    glVertex2i(64, 260);
    glVertex2i(20, 260);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(74, 160, 206);
    glVertex2i(20, 260);
    glVertex2i(64, 260);
    glVertex2i(64, 266);
    glVertex2i(20, 266);
    glEnd();

    //window 1
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(25, 237);
    glVertex2i(33, 237);
    glVertex2i(33, 250);
    glVertex2i(25, 250);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(25, 250);
    glVertex2i(33, 250);
    glVertex2i(33, 253);
    glVertex2i(25, 253);
    glEnd();

    //window 2
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(37, 237);
    glVertex2i(45, 237);
    glVertex2i(45, 250);
    glVertex2i(37, 250);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(37, 250);
    glVertex2i(45, 250);
    glVertex2i(45, 253);
    glVertex2i(37, 253);
    glEnd();

    //window 3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(50, 237);
    glVertex2i(58, 237);
    glVertex2i(58, 250);
    glVertex2i(50, 250);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(50, 250);
    glVertex2i(58, 250);
    glVertex2i(58, 253);
    glVertex2i(50, 253);
    glEnd();

    //window 4
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(25, 215);
    glVertex2i(33, 215);
    glVertex2i(33, 228);
    glVertex2i(25, 228);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(25, 228);
    glVertex2i(33, 228);
    glVertex2i(33, 231);
    glVertex2i(25, 231);
    glEnd();

    //window 5

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(37, 215);
    glVertex2i(45, 215);
    glVertex2i(45, 228);
    glVertex2i(37, 228);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(37, 228);
    glVertex2i(45, 228);
    glVertex2i(45, 231);
    glVertex2i(37, 231);
    glEnd();

    //window 6
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(50, 215);
    glVertex2i(58, 215);
    glVertex2i(58, 228);
    glVertex2i(50, 228);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(50, 228);
    glVertex2i(58, 228);
    glVertex2i(58, 231);
    glVertex2i(50, 231);
    glEnd();

    //window 7
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(25, 195);
    glVertex2i(33, 195);
    glVertex2i(33, 208);
    glVertex2i(25, 208);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(25, 207);
    glVertex2i(33, 207);
    glVertex2i(33, 210);
    glVertex2i(25, 210);
    glEnd();

    //window 8

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(37, 195);
    glVertex2i(45, 195);
    glVertex2i(45, 208);
    glVertex2i(37, 208);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(37, 207);
    glVertex2i(45, 207);
    glVertex2i(45, 210);
    glVertex2i(37, 210);
    glEnd();

    //window 9

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(50, 195);
    glVertex2i(58, 195);
    glVertex2i(58, 208);
    glVertex2i(50, 208);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(50, 207);
    glVertex2i(58, 207);
    glVertex2i(58, 210);
    glVertex2i(50, 210);
    glEnd();

    //window 10
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(25, 175);
    glVertex2i(33, 175);
    glVertex2i(33, 188);
    glVertex2i(25, 188);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(25, 188);
    glVertex2i(33, 188);
    glVertex2i(33, 191);
    glVertex2i(25, 191);
    glEnd();

   ///green building left 2

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(14, 12, 11);
    glVertex2i(90, 150);
    glVertex2i(100, 150);
    glVertex2i(100, 275);
    glVertex2i(90, 275);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(14, 12, 11);
    glVertex2i(85, 270);
    glVertex2i(95, 270);
    glVertex2i(95, 280);
    glVertex2i(85, 280);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(18, 73, 139);
    glVertex2i(100, 150);
    glVertex2i(160, 150);
    glVertex2i(160, 275);
    glVertex2i(100, 275);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(18, 73, 139);
    glVertex2i(90, 275);
    glVertex2i(165, 275);
    glVertex2i(165, 280);
    glVertex2i(90, 280);
    glEnd();

    //window 1
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(104, 245);
    glVertex2i(118, 245);
    glVertex2i(118, 265);
    glVertex2i(104, 265);
    glEnd();


    //window 2
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(124, 245);
    glVertex2i(138, 245);
    glVertex2i(138, 265);
    glVertex2i(124, 265);
    glEnd();


    //window 3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(142, 245);
    glVertex2i(156, 245);
    glVertex2i(156, 265);
    glVertex2i(142, 265);
    glEnd();


    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(8, 59, 135);
    glVertex2i(100, 237);
    glVertex2i(160, 237);
    glVertex2i(160, 240);
    glVertex2i(100, 240);
    glEnd();

    //window 4
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(104, 215);
    glVertex2i(118, 215);
    glVertex2i(118, 235);
    glVertex2i(104, 235);
    glEnd();



    //window 5
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(124, 215);
    glVertex2i(138, 215);
    glVertex2i(138, 235);
    glVertex2i(124, 235);
    glEnd();

    //window 6
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 5, 5);
    glVertex2i(142, 215);
    glVertex2i(156, 215);
    glVertex2i(156, 235);
    glVertex2i(142, 235);
    glEnd();


    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(8, 59, 135);
    glVertex2i(100, 207);
    glVertex2i(160, 207);
    glVertex2i(160, 210);
    glVertex2i(100, 210);
    glEnd();

    //window 7
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(104, 185);
    glVertex2i(118, 185);
    glVertex2i(118, 205);
    glVertex2i(104, 205);
    glEnd();


    //window 8
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(124, 185);
    glVertex2i(138, 185);
    glVertex2i(138, 205);
    glVertex2i(124, 205);
    glEnd();


    //window 9
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(135, 173, 149);
    glVertex2i(142, 185);
    glVertex2i(156, 185);
    glVertex2i(156, 205);
    glVertex2i(142, 205);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(107, 131, 125);
    glVertex2i(100, 177);
    glVertex2i(160, 177);
    glVertex2i(160, 180);
    glVertex2i(100, 180);
    glEnd();

    ///red building left 3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(17, 44, 76);
    glVertex2i(228, 145);
    glVertex2i(237, 145);
    glVertex2i(237, 310);
    glVertex2i(228, 310);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(17, 44, 76);
    glVertex2i(227, 305);
    glVertex2i(232, 305);
    glVertex2i(232, 315);
    glVertex2i(227, 315);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 112, 166);
    glVertex2i(237, 145);
    glVertex2i(300, 145);
    glVertex2i(300, 310);
    glVertex2i(237, 310);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 112, 166);
    glVertex2i(232, 310);
    glVertex2i(305, 310);
    glVertex2i(305, 315);
    glVertex2i(232, 315);
    glEnd();

    //window 1

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(250, 270);
    glVertex2i(262, 270);
    glVertex2i(262, 295);
    glVertex2i(250, 295);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(250, 285);
    glVertex2i(262, 285);
    glVertex2i(256, 270);
    glVertex2i(256, 295);
    glEnd();
    //window 2

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(267, 270);
    glVertex2i(279, 270);
    glVertex2i(279, 295);
    glVertex2i(267, 295);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(267, 285);
    glVertex2i(279, 285);
    glVertex2i(273, 270);
    glVertex2i(273, 295);
    glEnd();

    //window 3

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(284, 270);
    glVertex2i(296, 270);
    glVertex2i(296, 295);
    glVertex2i(284, 295);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(284, 285);
    glVertex2i(296, 285);
    glVertex2i(290, 270);
    glVertex2i(290, 295);
    glEnd();

    //window 4

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(250, 235);
    glVertex2i(262, 235);
    glVertex2i(262, 260);
    glVertex2i(250, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(250, 250);
    glVertex2i(262, 250);
    glVertex2i(256, 235);
    glVertex2i(256, 260);
    glEnd();

    //window 5

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(267, 235);
    glVertex2i(279, 235);
    glVertex2i(279, 260);
    glVertex2i(267, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(267, 250);
    glVertex2i(279, 250);
    glVertex2i(273, 235);
    glVertex2i(273, 260);
    glEnd();

    //window 6

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(284, 235);
    glVertex2i(296, 235);
    glVertex2i(296, 260);
    glVertex2i(284, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(284, 250);
    glVertex2i(296, 250);
    glVertex2i(290, 235);
    glVertex2i(290, 260);
    glEnd();

    //window 7

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(250, 195);
    glVertex2i(262, 195);
    glVertex2i(262, 220);
    glVertex2i(250, 220);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(250, 210);
    glVertex2i(262, 210);
    glVertex2i(256, 195);
    glVertex2i(256, 220);
    glEnd();

    //window 8

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(267, 195);
    glVertex2i(279, 195);
    glVertex2i(279, 220);
    glVertex2i(267, 220);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(267, 210);
    glVertex2i(279, 210);
    glVertex2i(273, 195);
    glVertex2i(273, 220);
    glEnd();

    //window 9

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 168, 49);
    glVertex2i(284, 195);
    glVertex2i(296, 195);
    glVertex2i(296, 220);
    glVertex2i(284, 220);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(151, 93, 17);
    glVertex2i(284, 210);
    glVertex2i(296, 210);
    glVertex2i(290, 195);
    glVertex2i(290, 220);
    glEnd();


    ///4th building left

    glBegin(GL_QUADS); ///side bar
    glPointSize(10.0);
    glColor3ub(7, 26, 33);
    glVertex2i(405, 145);
    glVertex2i(430, 145);
    glVertex2i(430, 330);
    glVertex2i(405, 330);
    glEnd();

    glBegin(GL_QUADS); ///main
    glPointSize(10.0);
    glColor3ub(34, 135, 197);
    glVertex2i(430, 145);
    glVertex2i(485, 145);
    glVertex2i(485, 330);
    glVertex2i(430, 330);
    glEnd();

    glBegin(GL_QUADS); ///top_side bar
    glPointSize(10.0);
    glColor3ub(16, 17, 8);
    glVertex2i(405, 330);
    glVertex2i(430, 330);
    glVertex2i(430, 336);
    glVertex2i(405, 336);
    glEnd();

    glBegin(GL_QUADS); ///top bottom bar
    glPointSize(10.0);
    glColor3ub(37, 142, 196);
    glVertex2i(430, 330);
    glVertex2i(485, 330);
    glVertex2i(485, 336);
    glVertex2i(430, 336);
    glEnd();

    glBegin(GL_QUADS); ///1st window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(436, 305);
    glVertex2i(446, 305);
    glVertex2i(446, 315);
    glVertex2i(436, 315);
    glEnd();



    glBegin(GL_QUADS); ///2nd window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(450, 305);
    glVertex2i(460, 305);
    glVertex2i(460, 315);
    glVertex2i(450, 315);
    glEnd();



    glBegin(GL_QUADS); ///3rd window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(465, 305);
    glVertex2i(475, 305);
    glVertex2i(475, 315);
    glVertex2i(465, 315);
    glEnd();


    glBegin(GL_QUADS); ///bottom bar
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 299);
    glVertex2i(475, 299);
    glVertex2i(475, 302);
    glVertex2i(435, 302);
    glEnd();

    glBegin(GL_QUADS); ///4th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(435, 265);
    glVertex2i(445, 265);
    glVertex2i(445, 275);
    glVertex2i(435, 275);
    glEnd();



    glBegin(GL_QUADS); ///6th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(465, 265);
    glVertex2i(475, 265);
    glVertex2i(475, 275);
    glVertex2i(465, 275);
    glEnd();



    glBegin(GL_QUADS); ///5th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(450, 265);
    glVertex2i(460, 265);
    glVertex2i(460, 275);
    glVertex2i(450, 275);
    glEnd();



    glBegin(GL_QUADS); ///2nd bottom bar
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 262);
    glVertex2i(475, 262);
    glVertex2i(475, 259);
    glVertex2i(435, 259);
    glEnd();

    glBegin(GL_QUADS); ///7th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(435, 220);
    glVertex2i(445, 220);
    glVertex2i(445, 230);
    glVertex2i(435, 230);
    glEnd();


    glBegin(GL_QUADS); ///8th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(450, 220);
    glVertex2i(460, 220);
    glVertex2i(460, 230);
    glVertex2i(450, 230);
    glEnd();



    glBegin(GL_QUADS); ///9th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(465, 220);
    glVertex2i(475, 220);
    glVertex2i(475, 230);
    glVertex2i(465, 230);
    glEnd();


    glBegin(GL_QUADS); ///3rd bottom bar
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 214);
    glVertex2i(475, 214);
    glVertex2i(475, 217);
    glVertex2i(435, 217);
    glEnd();

    glBegin(GL_QUADS); ///10th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(465, 175);
    glVertex2i(475, 175);
    glVertex2i(475, 185);
    glVertex2i(465, 185);
    glEnd();

    glBegin(GL_QUADS); ///11th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(435, 175);
    glVertex2i(445, 175);
    glVertex2i(445, 185);
    glVertex2i(435, 185);
    glEnd();


    glBegin(GL_QUADS); ///12th window
    glPointSize(10.0);
    glColor3ub(5, 45, 74);
    glVertex2i(450, 175);
    glVertex2i(460, 175);
    glVertex2i(460, 185);
    glVertex2i(450, 185);
    glEnd();


    glBegin(GL_QUADS); ///last bottom bar
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(435, 170);
    glVertex2i(475, 170);
    glVertex2i(475, 173);
    glVertex2i(435, 173);
    glEnd();

    /// 5 building left  tall

    glBegin(GL_QUADS); ///front
    glPointSize(10.0);
    glColor3ub(4, 110, 150);
    glVertex2i(645, 165);
    glVertex2i(705, 165);
    glVertex2i(705, 330);
    glVertex2i(645, 330);
    glEnd();

    glBegin(GL_QUADS); ///back
    glPointSize(10.0);
    glColor3ub(6, 45, 69);
    glVertex2i(705, 270);
    glVertex2i(725, 270);
    glVertex2i(725, 330);
    glVertex2i(705, 330);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 0, 0);
    glVertex2i(705, 330);
    glVertex2i(726, 330);
    glVertex2i(726, 335);
    glVertex2i(705, 335);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 111, 154);
    glVertex2i(642, 330);
    glVertex2i(705, 330);
    glVertex2i(705, 335);
    glVertex2i(642, 335);
    glEnd();

    //1st
    glBegin(GL_QUADS); ///window1
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(650, 300);
    glVertex2i(660, 300);
    glVertex2i(660, 315);
    glVertex2i(650, 315);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(650, 315);
    glVertex2i(660, 315);
    glVertex2i(660, 318);
    glVertex2i(650, 318);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(650, 270);
    glVertex2i(660, 270);
    glVertex2i(660, 285);
    glVertex2i(650, 285);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(650, 285);
    glVertex2i(660, 285);
    glVertex2i(660, 288);
    glVertex2i(650, 288);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(650, 240);
    glVertex2i(660, 240);
    glVertex2i(660, 255);
    glVertex2i(650, 255);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(650, 255);
    glVertex2i(660, 255);
    glVertex2i(660, 258);
    glVertex2i(650, 258);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(650, 210);
    glVertex2i(660, 210);
    glVertex2i(660, 225);
    glVertex2i(650, 225);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(650, 225);
    glVertex2i(660, 225);
    glVertex2i(660, 228);
    glVertex2i(650, 228);
    glEnd();

    //2nd
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(670, 300);
    glVertex2i(680, 300);
    glVertex2i(680, 315);
    glVertex2i(670, 315);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(670, 315);
    glVertex2i(680, 315);
    glVertex2i(680, 318);
    glVertex2i(670, 318);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(670, 270);
    glVertex2i(680, 270);
    glVertex2i(680, 285);
    glVertex2i(670, 285);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(670, 285);
    glVertex2i(680, 285);
    glVertex2i(680, 288);
    glVertex2i(670, 288);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(670, 240);
    glVertex2i(680, 240);
    glVertex2i(680, 255);
    glVertex2i(670, 255);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(670, 255);
    glVertex2i(680, 255);
    glVertex2i(680, 258);
    glVertex2i(670, 258);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(670, 210);
    glVertex2i(680, 210);
    glVertex2i(680, 225);
    glVertex2i(670, 225);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(670, 225);
    glVertex2i(680, 225);
    glVertex2i(680, 228);
    glVertex2i(670, 228);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(670, 180);
    glVertex2i(680, 180);
    glVertex2i(680, 195);
    glVertex2i(670, 195);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(670, 195);
    glVertex2i(680, 195);
    glVertex2i(680, 198);
    glVertex2i(670, 198);
    glEnd();

    //3rd

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(685, 300);
    glVertex2i(695, 300);
    glVertex2i(695, 315);
    glVertex2i(685, 315);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(685, 315);
    glVertex2i(695, 315);
    glVertex2i(695, 318);
    glVertex2i(685, 318);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(685, 270);
    glVertex2i(695, 270);
    glVertex2i(695, 285);
    glVertex2i(685, 285);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(685, 285);
    glVertex2i(695, 285);
    glVertex2i(695, 288);
    glVertex2i(685, 288);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(685, 240);
    glVertex2i(695, 240);
    glVertex2i(695, 255);
    glVertex2i(685, 255);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(685, 255);
    glVertex2i(695, 255);
    glVertex2i(695, 258);
    glVertex2i(685, 258);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(685, 210);
    glVertex2i(695, 210);
    glVertex2i(695, 225);
    glVertex2i(685, 225);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(160, 117, 50);
    glVertex2i(685, 225);
    glVertex2i(695, 225);
    glVertex2i(695, 228);
    glVertex2i(685, 228);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(685, 180);
    glVertex2i(695, 180);
    glVertex2i(695, 195);
    glVertex2i(685, 195);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(27, 174, 223);
    glVertex2i(685, 195);
    glVertex2i(695, 195);
    glVertex2i(695, 198);
    glVertex2i(685, 198);
    glEnd();

    ///5th building tall

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(12, 46, 80);
    glVertex2i(590, 145);
    glVertex2i(635, 145);
    glVertex2i(635, 200);
    glVertex2i(590, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(26, 155, 197);
    glVertex2i(635, 145);
    glVertex2i(685, 145);
    glVertex2i(685, 200);
    glVertex2i(635, 200);
    glEnd();

    //window 1
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(595, 190);
    glVertex2i(600, 190);
    glVertex2i(600, 185);
    glVertex2i(595, 185);
    glEnd();

    //window 2
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(602, 190);
    glVertex2i(607, 190);
    glVertex2i(607, 185);
    glVertex2i(602, 185);
    glEnd();

    //window 3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(609, 190);
    glVertex2i(614, 190);
    glVertex2i(614, 185);
    glVertex2i(609, 185);
    glEnd();

    //window 4
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(616, 190);
    glVertex2i(621, 190);
    glVertex2i(621, 185);
    glVertex2i(616, 185);
    glEnd();

    //window 5
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(623, 190);
    glVertex2i(628, 190);
    glVertex2i(628, 185);
    glVertex2i(623, 185);
    glEnd();

    //window 6
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(595, 175);
    glVertex2i(600, 175);
    glVertex2i(600, 180);
    glVertex2i(595, 180);
    glEnd();

    //window 7
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(602, 175);
    glVertex2i(607, 175);
    glVertex2i(607, 180);
    glVertex2i(602, 180);
    glEnd();

    //window 8
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(609, 175);
    glVertex2i(614, 175);
    glVertex2i(614, 180);
    glVertex2i(609, 180);
    glEnd();

    //window 9
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(616, 175);
    glVertex2i(621, 175);
    glVertex2i(621, 180);
    glVertex2i(616, 180);
    glEnd();

    //window 10
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(623, 175);
    glVertex2i(628, 175);
    glVertex2i(628, 180);
    glVertex2i(623, 180);
    glEnd();

    //window 11
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(595, 165);
    glVertex2i(600, 165);
    glVertex2i(600, 170);
    glVertex2i(595, 170);
    glEnd();

    //window 12
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(602, 165);
    glVertex2i(607, 165);
    glVertex2i(607, 170);
    glVertex2i(602, 170);
    glEnd();

    //window 13
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(609, 165);
    glVertex2i(614, 165);
    glVertex2i(614, 170);
    glVertex2i(609, 170);
    glEnd();

    //window 14
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(616, 165);
    glVertex2i(621, 165);
    glVertex2i(621, 170);
    glVertex2i(616, 170);
    glEnd();

    //window 15
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(623, 165);
    glVertex2i(628, 165);
    glVertex2i(628, 170);
    glVertex2i(623, 170);
    glEnd();

    //window 16
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(595, 155);
    glVertex2i(600, 155);
    glVertex2i(600, 160);
    glVertex2i(595, 160);
    glEnd();

    //window 17
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(602, 155);
    glVertex2i(607, 155);
    glVertex2i(607, 160);
    glVertex2i(602, 160);
    glEnd();

    //window 18
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(609, 155);
    glVertex2i(614, 155);
    glVertex2i(614, 160);
    glVertex2i(609, 160);
    glEnd();

    //window 19
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(616, 155);
    glVertex2i(621, 155);
    glVertex2i(621, 160);
    glVertex2i(616, 160);
    glEnd();

    //window 20
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(40, 102, 158);
    glVertex2i(623, 155);
    glVertex2i(628, 155);
    glVertex2i(628, 160);
    glVertex2i(623, 160);
    glEnd();

   ///6th building

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(6, 92, 119);
    glVertex2i(705, 145);
    glVertex2i(765, 145);
    glVertex2i(765, 270);
    glVertex2i(705, 270);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(16, 15, 16);
    glVertex2i(695, 145);
    glVertex2i(705, 145);
    glVertex2i(705, 270);
    glVertex2i(695, 270);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(720, 250);
    glVertex2i(730, 250);
    glVertex2i(730, 260);
    glVertex2i(720, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(720, 255);
    glVertex2i(730, 255);
    glVertex2i(725, 260);
    glVertex2i(725, 250);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 250);
    glVertex2i(743, 250);
    glVertex2i(743, 260);
    glVertex2i(733, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 255);
    glVertex2i(743, 255);
    glVertex2i(738, 260);
    glVertex2i(738, 250);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(745, 250);
    glVertex2i(755, 250);
    glVertex2i(755, 260);
    glVertex2i(745, 260);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(745, 255);
    glVertex2i(755, 255);
    glVertex2i(750, 260);
    glVertex2i(750, 250);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(720, 235);
    glVertex2i(730, 235);
    glVertex2i(730, 245);
    glVertex2i(720, 245);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(720, 240);
    glVertex2i(730, 240);
    glVertex2i(725, 245);
    glVertex2i(725, 235);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(720, 220);
    glVertex2i(730, 220);
    glVertex2i(730, 230);
    glVertex2i(720, 230);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(720, 225);
    glVertex2i(730, 225);
    glVertex2i(725, 230);
    glVertex2i(725, 220);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(720, 205);
    glVertex2i(730, 205);
    glVertex2i(730, 215);
    glVertex2i(720, 215);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(720, 210);
    glVertex2i(730, 210);
    glVertex2i(725, 215);
    glVertex2i(725, 205);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(720, 190);
    glVertex2i(730, 190);
    glVertex2i(730, 200);
    glVertex2i(720, 200);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(720, 195);
    glVertex2i(730, 195);
    glVertex2i(725, 200);
    glVertex2i(725, 190);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(720, 175);
    glVertex2i(730, 175);
    glVertex2i(730, 185);
    glVertex2i(720, 185);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(720, 180);
    glVertex2i(730, 180);
    glVertex2i(725, 185);
    glVertex2i(725, 175);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(720, 160);
    glVertex2i(730, 160);
    glVertex2i(730, 170);
    glVertex2i(720, 170);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(720, 165);
    glVertex2i(730, 165);
    glVertex2i(725, 170);
    glVertex2i(725, 160);
    glEnd();

    //2nd
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 235);
    glVertex2i(743, 235);
    glVertex2i(743, 245);
    glVertex2i(733, 245);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 240);
    glVertex2i(743, 240);
    glVertex2i(738, 245);
    glVertex2i(738, 235);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 220);
    glVertex2i(743, 220);
    glVertex2i(743, 230);
    glVertex2i(733, 230);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 225);
    glVertex2i(743, 225);
    glVertex2i(738, 230);
    glVertex2i(738, 220);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(733, 205);
    glVertex2i(743, 205);
    glVertex2i(743, 215);
    glVertex2i(733, 215);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(733, 210);
    glVertex2i(743, 210);
    glVertex2i(738, 215);
    glVertex2i(738, 205);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 190);
    glVertex2i(743, 190);
    glVertex2i(743, 200);
    glVertex2i(733, 200);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 195);
    glVertex2i(743, 195);
    glVertex2i(738, 200);
    glVertex2i(738, 190);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(733, 175);
    glVertex2i(743, 175);
    glVertex2i(743, 185);
    glVertex2i(733, 185);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(733, 180);
    glVertex2i(743, 180);
    glVertex2i(738, 185);
    glVertex2i(738, 175);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 160);
    glVertex2i(743, 160);
    glVertex2i(743, 170);
    glVertex2i(733, 170);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(733, 165);
    glVertex2i(743, 165);
    glVertex2i(738, 170);
    glVertex2i(738, 160);
    glEnd();

    //3rd
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(745, 235);
    glVertex2i(755, 235);
    glVertex2i(755, 245);
    glVertex2i(745, 245);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(745, 240);
    glVertex2i(755, 240);
    glVertex2i(750, 245);
    glVertex2i(750, 235);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(745, 220);
    glVertex2i(755, 220);
    glVertex2i(755, 230);
    glVertex2i(745, 230);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(745, 225);
    glVertex2i(755, 225);
    glVertex2i(750, 230);
    glVertex2i(750, 220);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(745, 205);
    glVertex2i(755, 205);
    glVertex2i(755, 215);
    glVertex2i(745, 215);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(745, 210);
    glVertex2i(755, 210);
    glVertex2i(750, 215);
    glVertex2i(750, 205);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(745, 190);
    glVertex2i(755, 190);
    glVertex2i(755, 200);
    glVertex2i(745, 200);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(745, 195);
    glVertex2i(755, 195);
    glVertex2i(750, 200);
    glVertex2i(750, 190);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(246, 184, 10);
    glVertex2i(745, 175);
    glVertex2i(755, 175);
    glVertex2i(755, 185);
    glVertex2i(745, 185);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(246, 184, 10);
    glVertex2i(745, 180);
    glVertex2i(755, 180);
    glVertex2i(750, 185);
    glVertex2i(750, 175);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(9, 38, 58);
    glVertex2i(745, 160);
    glVertex2i(755, 160);
    glVertex2i(755, 170);
    glVertex2i(745, 170);
    glEnd();

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(9, 38, 58);
    glVertex2i(745, 165);
    glVertex2i(755, 165);
    glVertex2i(750, 170);
    glVertex2i(750, 160);
    glEnd();

   ///2nd building
    glBegin(GL_QUADS); //red1 b2
    glPointSize(10.0);
    glColor3ub(6, 41, 50);
    glVertex2i(855, 155);
    glVertex2i(865, 155);
    glVertex2i(865, 330);
    glVertex2i(855, 330);
    glEnd();

    glBegin(GL_QUADS); //red2 b2 border
    glPointSize(10.0);
    glColor3ub(6, 41, 50);
    glVertex2i(850, 325);
    glVertex2i(865, 325);
    glVertex2i(865, 335);
    glVertex2i(850, 335);
    glEnd();
    glBegin(GL_QUADS); //green1 b2
    glPointSize(10.0);
    glColor3ub(3, 125, 164);
    glVertex2i(865, 155);
    glVertex2i(925, 155);
    glVertex2i(925, 330);
    glVertex2i(865, 330);
    glEnd();
    glBegin(GL_QUADS); //green2 b2 border
    glPointSize(10.0);
    glColor3ub(3, 125, 164);
    glVertex2i(860, 325);
    glVertex2i(930, 325);
    glVertex2i(930, 335);
    glVertex2i(860, 335);
    glEnd();
    glBegin(GL_QUADS); //w1 b2
    glPointSize(10.0);
    glColor3ub(204, 160, 65);
    glVertex2i(870, 290);
    glVertex2i(885, 290);
    glVertex2i(885, 310);
    glVertex2i(870, 310);
    glEnd();
    glBegin(GL_QUADS); //w2 b2
    glPointSize(10.0);
    glColor3ub(2, 52, 75);
    glVertex2i(890, 290);
    glVertex2i(905, 290);
    glVertex2i(905, 310);
    glVertex2i(890, 310);
    glEnd();
    glBegin(GL_QUADS); //w3 b2
    glPointSize(10.0);
    glColor3ub(2, 52, 75);
    glVertex2i(910, 290);
    glVertex2i(925, 290);
    glVertex2i(925, 310);
    glVertex2i(910, 310);
    glEnd();
    //line border1

    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(2, 52, 75);
    glVertex2i(867, 282);
    glVertex2i(923, 282);
    glEnd();

    glBegin(GL_QUADS); //w4 b2
    glPointSize(10.0);
    glColor3ub(2, 52, 75);
    glVertex2i(870, 255);
    glVertex2i(885, 255);
    glVertex2i(885, 275);
    glVertex2i(870, 275);
    glEnd();
    glBegin(GL_QUADS); //w5 b2
    glPointSize(10.0);
    glColor3ub(204, 160, 65);
    glVertex2i(890, 255);
    glVertex2i(905, 255);
    glVertex2i(905, 275);
    glVertex2i(890, 275);
    glEnd();

    glBegin(GL_QUADS); //w6 b2
    glPointSize(10.0);
    glColor3ub(204, 160, 65);
    glVertex2i(910, 255);
    glVertex2i(925, 255);
    glVertex2i(925, 275);
    glVertex2i(910, 275);
    glEnd();
    //line border2
    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(2, 52, 75);
    glVertex2i(867, 244);
    glVertex2i(923, 244);
    glEnd();

    glBegin(GL_QUADS); //w7 b2
    glPointSize(10.0);
    glColor3ub(2, 52, 75);
    glVertex2i(870, 220);
    glVertex2i(885, 220);
    glVertex2i(885, 240);
    glVertex2i(870, 240);
    glEnd();

    glBegin(GL_QUADS); //w8 b2
    glPointSize(10.0);
    glColor3ub(204, 160, 65);
    glVertex2i(890, 220);
    glVertex2i(905, 220);
    glVertex2i(905, 240);
    glVertex2i(890, 240);
    glEnd();

    glBegin(GL_QUADS); //w9 b2
    glPointSize(10.0);
    glColor3ub(2, 52, 75);
    glVertex2i(910, 220);
    glVertex2i(925, 220);
    glVertex2i(925, 240);
    glVertex2i(910, 240);
    glEnd();

    //line border3
    glBegin(GL_LINES);
    glLineWidth(10);
    glColor3ub(2, 52, 75);
    glVertex2i(867, 204);
    glVertex2i(923, 204);
    glEnd();

    ///2nd building right
    glBegin(GL_QUADS); //b3 border
    glPointSize(10.0);
    glColor3ub(8, 90, 117);
    glVertex2i(924, 145);
    glVertex2i(934, 145);
    glVertex2i(934, 252);
    glVertex2i(924, 252);
    glEnd();
    //Red part b3
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(98, 161, 199);
    glVertex2i(934, 145);
    glVertex2i(995, 145);
    glVertex2i(995, 252);
    glVertex2i(934, 252);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 30, 49); //w1 b3
    glVertex2i(952, 235);
    glVertex2i(960, 235);
    glVertex2i(960, 245);
    glVertex2i(952, 245);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 30, 49); //w2 b3
    glVertex2i(975, 235);
    glVertex2i(984, 235);
    glVertex2i(984, 245);
    glVertex2i(975, 245);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 184, 0); //w3 b3
    glVertex2i(940, 220);
    glVertex2i(950, 220);
    glVertex2i(950, 230);
    glVertex2i(940, 230);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 184, 0); //w4 b3
    glVertex2i(963, 220);
    glVertex2i(973, 220);
    glVertex2i(973, 232);
    glVertex2i(963, 232);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 30, 49); //w5 b3
    glVertex2i(952, 205);
    glVertex2i(960, 205);
    glVertex2i(960, 215);
    glVertex2i(952, 215);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 30, 49); //w6 b3
    glVertex2i(975, 205);
    glVertex2i(984, 205);
    glVertex2i(984, 215);
    glVertex2i(975, 215);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 30, 49); //w7 b3
    glVertex2i(940, 190);
    glVertex2i(950, 190);
    glVertex2i(950, 200);
    glVertex2i(940, 200);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 184, 0); //w8 b3
    glVertex2i(963, 190);
    glVertex2i(973, 190);
    glVertex2i(973, 200);
    glVertex2i(963, 200);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 184, 0); //w9 b3
    glVertex2i(952, 180);
    glVertex2i(960, 180);
    glVertex2i(960, 190);
    glVertex2i(952, 190);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 30, 49); //w10 b3
    glVertex2i(975, 180);
    glVertex2i(984, 180);
    glVertex2i(984, 190);
    glVertex2i(975, 190);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 30, 49); //w11 b3
    glVertex2i(940, 165);
    glVertex2i(950, 165);
    glVertex2i(950, 175);
    glVertex2i(940, 175);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 184, 0); //w12 b3
    glVertex2i(963, 165);
    glVertex2i(973, 165);
    glVertex2i(973, 175);
    glVertex2i(963, 175);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(2, 30, 49); //w13 b3
    glVertex2i(952, 150);
    glVertex2i(960, 150);
    glVertex2i(960, 160);
    glVertex2i(952, 160);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(255, 184, 0); //w14 b3
    glVertex2i(975, 150);
    glVertex2i(984, 150);
    glVertex2i(984, 160);
    glVertex2i(975, 160);
    glEnd();

    /// 1st  building right
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(0, 136, 173);
    glVertex2i(1010, 147);
    glVertex2i(1025, 147);
    glVertex2i(1025, 208);
    glVertex2i(1010, 208);
    glEnd();

    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(1, 20, 29); //deep oranger part b4
    glVertex2i(1025, 147);
    glVertex2i(1030, 147);
    glVertex2i(1030, 208);
    glVertex2i(1025, 208);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(11, 46, 84); //light oranger part b4
    glVertex2i(1030, 147);
    glVertex2i(1060, 147);
    glVertex2i(1060, 208);
    glVertex2i(1030, 208);
    glEnd();
    glBegin(GL_QUADS); //light brik 1
    glPointSize(10.0);
    glColor3ub(0, 136, 173);
    glVertex2i(1060, 147);
    glVertex2i(1074, 147);
    glVertex2i(1074, 208);
    glVertex2i(1060, 208);
    glEnd();
    glBegin(GL_QUADS); //light brik 2
    glPointSize(10.0);
    glColor3ub(0, 136, 173);
    glVertex2i(1060, 147);
    glVertex2i(1074, 147);
    glVertex2i(1074, 208);
    glVertex2i(1060, 208);
    glEnd();
    glBegin(GL_QUADS); //light brik square
    glPointSize(10.0);
    glColor3ub(0, 136, 173);
    glVertex2i(1010, 208);
    glVertex2i(1074, 208);
    glVertex2i(1074, 233);
    glVertex2i(1010, 233);
    glEnd();
    glBegin(GL_QUADS); //white border
    glPointSize(10.0);
    glColor3ub(0, 22, 32);
    glVertex2i(1010, 233);
    glVertex2i(1074, 233);
    glVertex2i(1074, 239);
    glVertex2i(1010, 239);
    glEnd();
    glBegin(GL_QUADS); //upper brik
    glPointSize(10.0);
    glColor3ub(0, 136, 173);
    glVertex2i(1010, 239);
    glVertex2i(1074, 239);
    glVertex2i(1074, 282);
    glVertex2i(1010, 282);
    glEnd();
    glBegin(GL_QUADS); //W1
    glPointSize(10.0);
    glColor3ub(4, 27, 40);
    glVertex2i(1018, 260);
    glVertex2i(1024, 260);
    glVertex2i(1024, 270);
    glVertex2i(1018, 270);
    glEnd();
    glBegin(GL_QUADS); //W2
    glPointSize(10.0);
    glColor3ub(4, 27, 40);
    glVertex2i(1028, 260);
    glVertex2i(1035, 260);
    glVertex2i(1035, 270);
    glVertex2i(1028, 270);
    glEnd();
    glBegin(GL_QUADS); //W3
    glPointSize(10.0);
    glColor3ub(248, 190, 25);
    glVertex2i(1038, 260);
    glVertex2i(1045, 260);
    glVertex2i(1045, 270);
    glVertex2i(1038, 270);
    glEnd();
    glBegin(GL_QUADS); //W4
    glPointSize(10.0);
    glColor3ub(4, 27, 40);
    glVertex2i(1048, 260);
    glVertex2i(1055, 260);
    glVertex2i(1055, 270);
    glVertex2i(1048, 270);
    glEnd();
    glBegin(GL_QUADS); //W5
    glPointSize(10.0);
    glColor3ub(4, 27, 40);
    glVertex2i(1018, 249);
    glVertex2i(1024, 249);
    glVertex2i(1024, 258);
    glVertex2i(1018, 258);
    glEnd();
    glBegin(GL_QUADS); //W6
    glPointSize(10.0);
    glColor3ub(248, 190, 25);
    glVertex2i(1028, 249);
    glVertex2i(1035, 249);
    glVertex2i(1035, 258);
    glVertex2i(1028, 258);
    glEnd();
    glBegin(GL_QUADS); //W6
    glPointSize(10.0);
    glColor3ub(4, 27, 40);
    glVertex2i(1038, 249);
    glVertex2i(1045, 249);
    glVertex2i(1045, 258);
    glVertex2i(1038, 258);
    glEnd();
    glBegin(GL_QUADS); //W7
    glPointSize(10.0);
    glColor3ub(4, 27, 40);
    glVertex2i(1038, 249);
    glVertex2i(1045, 249);
    glVertex2i(1045, 258);
    glVertex2i(1038, 258);
    glEnd();
    glBegin(GL_QUADS); //W8
    glPointSize(10.0);
    glColor3ub(248, 190, 25);
    glVertex2i(1048, 249);
    glVertex2i(1055, 249);
    glVertex2i(1055, 258);
    glVertex2i(1048, 258);
    glEnd();
    //uppper triangle
    glBegin(GL_TRIANGLES);
    glPointSize(10.0);
    glColor3ub(112, 182, 228);
    glVertex2i(1010, 282);
    glVertex2i(1073, 282);
    glVertex2i(1053, 315);
    glEnd();
    glBegin(GL_QUADS); //deep border
    glPointSize(10.0);
    glColor3ub(112, 182, 228);
    glVertex2i(1010, 282);
    glVertex2i(1072, 282);
    glVertex2i(1072, 288);
    glVertex2i(1014, 288);
    glEnd();

    glBegin(GL_TRIANGLES);
    glPointSize(10.0);
    glColor3ub(5, 47, 72);
    glVertex2i(1073, 282);
    glVertex2i(1097, 282);
    glVertex2i(1053, 315);
    glEnd();
    glBegin(GL_QUADS);
    glPointSize(10.0);
    glColor3ub(5, 47, 72);
    glVertex2i(1074, 147);
    glVertex2i(1097, 147);
    glVertex2i(1097, 282);
    glVertex2i(1074, 282);
    glEnd();
    glBegin(GL_QUADS); //w1
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1080, 262);
    glVertex2i(1085, 262);
    glVertex2i(1085, 273);
    glVertex2i(1080, 273);
    glEnd();
    glBegin(GL_QUADS); //w2
    glPointSize(10.0);
    glColor3ub(244, 190, 32);
    glVertex2i(1088, 263);
    glVertex2i(1093, 263);
    glVertex2i(1093, 273);
    glVertex2i(1088, 273);
    glEnd();
    glBegin(GL_QUADS); //w3
    glPointSize(10.0);
    glColor3ub(244, 190, 32);
    glVertex2i(1080, 249);
    glVertex2i(1085, 249);
    glVertex2i(1085, 258);
    glVertex2i(1080, 258);
    glEnd();
    glBegin(GL_QUADS); //w4
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1088, 249);
    glVertex2i(1093, 249);
    glVertex2i(1093, 258);
    glVertex2i(1088, 258);
    glEnd();
    glBegin(GL_QUADS); //w5
    glPointSize(10.0);
    glColor3ub(244, 190, 32);
    glVertex2i(1080, 232);
    glVertex2i(1085, 232);
    glVertex2i(1085, 244);
    glVertex2i(1080, 244);
    glEnd();
    glBegin(GL_QUADS); //w6
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1088, 232);
    glVertex2i(1093, 232);
    glVertex2i(1093, 244);
    glVertex2i(1088, 244);
    glEnd();

    glBegin(GL_QUADS); //w7
    glPointSize(10.0);
    glColor3ub(244, 190, 32);
    glVertex2i(1080, 216);
    glVertex2i(1085, 216);
    glVertex2i(1085, 228);
    glVertex2i(1080, 228);
    glEnd();
    glBegin(GL_QUADS); //w8
    glPointSize(10.0);
    glColor3ub(244, 190, 32);
    glVertex2i(1088, 216);
    glVertex2i(1093, 216);
    glVertex2i(1093, 228);
    glVertex2i(1088, 228);
    glEnd();
    glBegin(GL_QUADS); //w9
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1080, 204);
    glVertex2i(1085, 204);
    glVertex2i(1085, 213);
    glVertex2i(1080, 213);
    glEnd();
    glBegin(GL_QUADS); //w10
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1088, 204);
    glVertex2i(1093, 204);
    glVertex2i(1093, 213);
    glVertex2i(1088, 213);
    glEnd();
    glBegin(GL_QUADS); //w11
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1080, 188);
    glVertex2i(1085, 188);
    glVertex2i(1085, 198);
    glVertex2i(1080, 198);
    glEnd();
    glBegin(GL_QUADS); //w12
    glPointSize(10.0);
    glColor3ub(244, 190, 32);
    glVertex2i(1088, 188);
    glVertex2i(1093, 188);
    glVertex2i(1093, 198);
    glVertex2i(1088, 198);
    glEnd();

    glBegin(GL_QUADS); //w13
    glPointSize(10.0);
    glColor3ub(244, 190, 32);
    glVertex2i(1080, 173);
    glVertex2i(1085, 173);
    glVertex2i(1085, 182);
    glVertex2i(1080, 182);
    glEnd();
    glBegin(GL_QUADS); //w14
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1088, 173);
    glVertex2i(1093, 173);
    glVertex2i(1093, 182);
    glVertex2i(1088, 182);
    glEnd();
    glBegin(GL_QUADS); //w15
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1080, 157);
    glVertex2i(1085, 157);
    glVertex2i(1085, 169);
    glVertex2i(1080, 169);
    glEnd();
    glBegin(GL_QUADS); //w16
    glPointSize(10.0);
    glColor3ub(5, 28, 38);
    glVertex2i(1088, 157);
    glVertex2i(1093, 157);
    glVertex2i(1093, 169);
    glVertex2i(1088, 169);
    glEnd();

}// To track if cloud is moving

void Day_r()
{
    Daysky();

    if (sunY < -60)
        if (!rainday)
            EveningSky();

    sunRise();
    sunset();

    ///Display the mouse click instructions for cloud movement
    text(10, 560, "Press Mouse click to move the cloud right and left to stop");
    text(10, 580, "Press S to stop the car");
    text(170, 540, "Press g to start the car");

    if (rainday)
    {
        text(170, 580, "Press F to stop Rain");
    }
    else
    {
        text(170, 580, "Press R to start Rain");
    }

    moveCloud();
    BgBuildingDayTime();
    RoadFieldDay();
    DayTime();
    dayTree();
    vehicle();
    dayLampPost();
    glutSwapBuffers();
}

void Night_r()
{
    Nightsky();
    MoonRise();
    moonset();
    text(10, 560, "Press Mouse click to move the cloud right and left to stop");
    text(10, 580, "Press S to stop the car");
    text(170, 540, "Press g to start the car");
    if (rainday)
    {
        text(170, 580, "Press F to stop Rain");
    }
    else
        text(170, 580, "Press R to start Rain");
    moveCloud();
    BgBuildingNightTime();
    RoadFielNight();
    NightTime();
    nightTree();
    vehicle();
    nightLampPost();
    glutSwapBuffers();
}




void myInit(void)
{
    glClearColor(255, 255, 255, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1200.0, 0.0, 600.0);
}










/*--------------Sani------------------*/



bool isNight_S = false;
bool Rain_Sday_S = false;


/*----------cloudS Code------------*/


float cloudSS = 0;
float cloudSS2 = 0;

// Function to draw a filled circle
void DrawCircle1(float cx, float cy, float r, int num_segments)
{
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < num_segments; i++)
    {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

struct cloudS
{
    void drawDaycloudS()
    {
        if (isNight_S) {
            glColor3ub(105, 105, 105);
        } else {
            glColor3ub(255, 255, 255);
        }
        DrawCircle(246, 486, 23, 100); // cloudS part 1
        DrawCircle(290, 509, 40, 100); // cloudS part 2
        DrawCircle(350, 494, 36, 100); // cloudS part 3

        // Connecting rectangle
        glBegin(GL_QUADS);
        glVertex2i(246, 480);
        glVertex2i(246, 463);
        glVertex2i(350, 459);
        glVertex2i(350, 480);
        glEnd();
    }

    void DaycloudS()
    {
        glPushMatrix();
        glTranslatef(cloudSS, cloudSS2, 0); // Apply translation for movement

        // cloudS 1
        glPushMatrix();
        glTranslated(350, -25, 0);
        drawDaycloudS();
        glPopMatrix();

        // cloudS 2
        glPushMatrix();
        glTranslated(-150, 0, 0);
        drawDaycloudS();
        glPopMatrix();

        // cloudS 3
        glPushMatrix();
        glTranslated(200, 50, 0);
        drawDaycloudS();
        glPopMatrix();

        // cloudS 4
        glPushMatrix();
        glTranslated(600, -0, 0);
        drawDaycloudS();
        glPopMatrix();

        glPopMatrix();
    }

    void movecloudS()
    {
        cloudSS += 0.8;
        if (cloudSS > 1200)
        {
            cloudSS2 = -1200;
        }
    }
};

cloudS cloudSObj; //global variable

void timer(int)
{
    cloudSObj.movecloudS();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}


/*--------Sky Code----------*/

void DaySky_S()
{
    if (isNight_S) {
        glColor3ub(25, 25, 112); // Night sky
    } else {
        glColor3ub(135, 206, 235); // Day sky
    }
    glBegin(GL_QUADS);
    glVertex2i(0, 600);
    glVertex2i(0, 300);
    glVertex2i(1200, 300);
    glVertex2i(1200, 600);
    glEnd();
}


/*-----------Rain_S Code-----------*/


void Sun_S()
{
    if (isNight_S) {
        glColor3ub(200, 200, 200); // Moon color
    } else {
        glColor3ub(255, 255, 0); // Sun_S color
    }

    if(!Rain_Sday_S)
    {
    glBegin(GL_TRIANGLE_FAN);
    int Sun_SCenterX = 1000;
    int Sun_SCenterY = 500;
    float Sun_SRadius = 60.0;

    for (int angle = 0; angle <= 360; angle += 10) {
        float theta = angle * (M_PI / 180.0);
        glVertex2d(Sun_SCenterX + Sun_SRadius * cos(theta),
                   Sun_SCenterY + Sun_SRadius * sin(theta));
    }
    glEnd();

    }
}

void DayBuilding1_S()
{

    if (isNight_S) {
        glColor3ub(50, 50, 50); // Darker building
    } else {
        glColor3ub(255, 230, 0);
    }
    // Side pillar
    glBegin(GL_QUADS);
    glVertex2i(10, 220);
    glVertex2i(30, 220);
    glVertex2i(30, 460);
    glVertex2i(10, 440);
    glEnd();

    if (isNight_S) {
        glColor3ub(50, 50, 50); // Darker building
    } else {
        glColor3ub(255, 255, 0);
    }
    // Body
    glBegin(GL_QUADS);
    glVertex2i(30, 220);
    glVertex2i(90, 220);
    glVertex2i(90, 460);
    glVertex2i(30, 460);
    glEnd();

    int xStart = 38, yStart = 420;
    int windowWidth = 10, windowHeight = 10;
    int windowSpacing = 15;

    // Loop through all window positions (21 windows)
    for (int i = 0; i < 21; ++i)
    {
        int xPos = xStart + (i % 3) * windowSpacing;
        int yPos = yStart - (i / 3) * windowSpacing;

        if (isNight_S) {
        glColor3ub(255, 140, 0); // Orange window light for night
    } else {
        glColor3ub(100, 70, 255);
    }
        glBegin(GL_QUADS);
        glVertex2i(xPos, yPos);
        glVertex2i(xPos + windowWidth, yPos);
        glVertex2i(xPos + windowWidth, yPos + windowHeight);
        glVertex2i(xPos, yPos + windowHeight);
        glEnd();
    }

}

//void NightBuilding_S()

//Building 2
void DayBuilding2_S() {

    if (isNight_S) {
        glColor3ub(80, 50, 50);
    } else {
        glColor3ub(200, 99, 71);
    }
    glBegin(GL_QUADS);
    glVertex2i(100, 220);
    glVertex2i(116, 220);
    glVertex2i(116, 460);
    glVertex2i(100, 460);
    glEnd();

    //Body
    if (isNight_S) {
        glColor3ub(30, 30, 60); // Darker building
    } else {
        glColor3ub(255, 99, 71);
    }
    glBegin(GL_QUADS);
    glVertex2i(116, 220);
    glVertex2i(189, 220);
    glVertex2i(189, 460);
    glVertex2i(116, 460);
    glEnd();

    //Window
    if (isNight_S) {
        glColor3ub(255, 233, 100); // Darker building
    } else {
        glColor3ub(100, 70, 255);
    }
    // Draw windows 1-3 (vertical windows)
    for (int i = 0; i < 3; ++i) {
        int x1 = 126 + (i * 20); // Offset X position for each window
        glBegin(GL_QUADS);
        glVertex2i(x1, 440); // Offset Y positions
        glVertex2i(x1 + 13, 440);
        glVertex2i(x1 + 13, 425);
        glVertex2i(x1, 425);
        glEnd();
    }

    // Draw windows 4-6 (vertical windows)
    for (int i = 0; i < 3; ++i) {
        int x1 = 126 + (i * 20); // Offset X position for each window
        glBegin(GL_QUADS);
        glVertex2i(x1, 415); // Offset Y positions
        glVertex2i(x1 + 13, 415);
        glVertex2i(x1 + 13, 400);
        glVertex2i(x1, 400);
        glEnd();
    }

    // Draw windows 7-9 (vertical windows)
    for (int i = 0; i < 3; ++i) {
        int x1 = 126 + (i * 20); // Offset X position for each window
        glBegin(GL_QUADS);
        glVertex2i(x1, 390); // Offset Y positions
        glVertex2i(x1 + 13, 390);
        glVertex2i(x1 + 13, 375);
        glVertex2i(x1, 375);
        glEnd();
    }
}

//Building 3
void DayBuilding3_S()
{
    if (isNight_S) {
        glColor3ub(120, 120, 50);
    } else {
        glColor3ub(200, 200, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(200, 220);
    glVertex2i(216, 220);
    glVertex2i(216, 460);
    glVertex2i(200, 460);
    glEnd();

    // Body
    if (isNight_S) {
        glColor3ub(150, 150, 50); // Darker building
    } else {
        glColor3ub(250, 250, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(216, 220);
    glVertex2i(289, 220);
    glVertex2i(289, 460);
    glVertex2i(216, 460);
    glEnd();

    // Loop for drawing windows 1-9 (positioned similarly)
    if (isNight_S) {
        glColor3ub(255, 233, 100); // Darker building
    } else {
        glColor3ub(100, 70, 255);
    }

    // Draw windows 1-3 (vertical windows)
    for (int i = 0; i < 3; ++i) {
        int x1 = 227 + (i * 20); // X position for each window
        glBegin(GL_QUADS);
        glVertex2i(x1, 440);
        glVertex2i(x1 + 13, 440);
        glVertex2i(x1 + 13, 425);
        glVertex2i(x1, 425);
        glEnd();
    }

    // Draw windows 4-6 (vertical windows)
    for (int i = 0; i < 3; ++i) {
        int x1 = 227 + (i * 20); // X position for each window
        glBegin(GL_QUADS);
        glVertex2i(x1, 415);
        glVertex2i(x1 + 13, 415);
        glVertex2i(x1 + 13, 400);
        glVertex2i(x1, 400);
        glEnd();
    }

    // Draw windows 7-9 (vertical windows)
    for (int i = 0; i < 3; ++i) {
        int x1 = 227 + (i * 20); // X position for each window
        glBegin(GL_QUADS);
        glVertex2i(x1, 390);
        glVertex2i(x1 + 13, 390);
        glVertex2i(x1 + 13, 375);
        glVertex2i(x1, 375);
        glEnd();
    }
}

void DayBuilding4_S()
{

    // Side pillar
    if (isNight_S) {
        glColor3ub(100, 45, 0); // Darker building
    } else {
        glColor3ub(195, 90, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(300, 220);
    glVertex2i(320, 220);
    glVertex2i(320, 460);
    glVertex2i(300, 440);
    glEnd();

    // Body
    if (isNight_S) {
        glColor3ub(120, 70, 10);
    } else {
        glColor3ub(255, 140, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(320, 220);
    glVertex2i(375, 220);
    glVertex2i(375, 460);
    glVertex2i(320, 460);
    glEnd();

    int xStart = 328, yStart = 420;
    int Width = 10, Height = 10;
    int Spacing = 15; // Space between windows

    // Loop through all window positions (21 windows)
    for (int i = 0; i < 21; ++i)
    {
        int xPos = xStart + (i % 3) * Spacing; // 3 windows per row
        int yPos = yStart - (i / 3) * Spacing;

        if (isNight_S) {
        glColor3ub(255, 233, 100); // Darker building
        }   else {
        glColor3ub(100, 70, 255);
        }
        glBegin(GL_QUADS);
        glVertex2i(xPos, yPos);
        glVertex2i(xPos + Width, yPos);
        glVertex2i(xPos + Width, yPos + Height);
        glVertex2i(xPos, yPos + Height);
        glEnd();
    }
}



/*------------Stationary Shop---------------*/

void StationaryShop()
{
    //Ground
    if (isNight_S) {
        glColor3ub(30, 30, 30);
    } else {
        glColor3ub(0, 0, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(5, 140);
    glVertex2i(375, 140);
    glVertex2i(375, 145);
    glVertex2i(5, 145);
    glEnd();

    //Body
    if (isNight_S) {
        glColor3ub(80, 50, 20);
    } else {
        glColor3ub(251, 176, 59);
    }
    glBegin(GL_QUADS);
    glVertex2i(10, 145);
    glVertex2i(370, 145);
    glVertex2i(370, 350);
    glVertex2i(10, 350);
    glEnd();

    // Lower Round
    if (isNight_S) {
        glColor3ub(100, 60, 30);
    } else {
        glColor3ub(190, 143, 69);
    }
    glBegin(GL_QUADS);
    glVertex2i(4, 220);
    glVertex2i(380, 220);
    glVertex2i(380, 260);
    glVertex2i(4, 260);
    glEnd();

    // Round Angle 1
    if (isNight_S) {
        glColor3ub(100, 60, 30);
    } else {
        glColor3ub(190, 143, 69);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(4, 220);
    glVertex2i(10, 215);
    glVertex2i(10, 220);
    glEnd();

    // Round Angle 2
    glColor3ub(190, 143, 69);
    glBegin(GL_TRIANGLES);
    glVertex2i(370, 212);
    glVertex2i(380, 220);
    glVertex2i(370, 220);
    glEnd();

    //Left Window Bar
    if (isNight_S) {
        glColor3ub(30, 30, 30);
    } else {
        glColor3ub(0, 0, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(20, 155);
    glVertex2i(80, 155);
    glVertex2i(80, 200);
    glVertex2i(20, 200);
    glEnd();

    //Left Window
    if (isNight_S) {
        glColor3ub(255, 220, 120);
    } else {
        glColor3ub(221, 241, 250);
    }
    glBegin(GL_QUADS);
    glVertex2i(25, 160);
    glVertex2i(75, 160);
    glVertex2i(75, 195);
    glVertex2i(25, 195);
    glEnd();

    //Right Window Bar
    if (isNight_S) {
        glColor3ub(30, 30, 30);
    } else {
        glColor3ub(0, 0, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(280, 155);
    glVertex2i(340, 155);
    glVertex2i(340, 200);
    glVertex2i(280, 200);
    glEnd();

    //Right Window
    if (isNight_S) {
        glColor3ub(255, 220, 120);
    } else {
        glColor3ub(221, 241, 250);
    }
    glBegin(GL_QUADS);
    glVertex2i(285, 160);
    glVertex2i(335, 160);
    glVertex2i(335, 195);
    glVertex2i(285, 195);
    glEnd();

    //Door Left Bar
    if (isNight_S) {
        glColor3ub(100, 60, 30);
    } else {
        glColor3ub(166, 124, 82);
    }
    glBegin(GL_QUADS);
    glVertex2i(90, 145);
    glVertex2i(100, 145);
    glVertex2i(100, 220);
    glVertex2i(90, 220);
    glEnd();

    //Door Right Bar
    if (isNight_S) {
        glColor3ub(100, 60, 30);
    } else {
        glColor3ub(166, 124, 82);
    }
    glBegin(GL_QUADS);
    glVertex2i(270, 145);
    glVertex2i(260, 145);
    glVertex2i(260, 220);
    glVertex2i(270, 220);
    glEnd();

    //Door Glass
    if (isNight_S) {
        glColor3ub(40, 55, 75);
    } else {
        glColor3ub(221, 241, 250);
    }
    glBegin(GL_QUADS);
    glVertex2i(100, 145);
    glVertex2i(260, 145);
    glVertex2i(260, 220);
    glVertex2i(100, 220);
    glEnd();

    //Door Glass Bar
    glColor3ub(105, 105, 105);
    glBegin(GL_QUADS);
    glVertex2i(175, 145);
    glVertex2i(185, 145);
    glVertex2i(185, 220);
    glVertex2i(175, 220);
    glEnd();

    // Upper Round
    if (isNight_S) {
        glColor3ub(100, 60, 30);
    } else {
        glColor3ub(190, 143, 69);
    }
    glBegin(GL_QUADS);
    glVertex2i(4, 340);
    glVertex2i(380, 340);
    glVertex2i(380, 370);
    glVertex2i(4, 370);
    glEnd();

    // Round Angle 1
    glColor3ub(190, 143, 69);
    glBegin(GL_TRIANGLES);
    glVertex2i(4, 340);
    glVertex2i(10, 335);
    glVertex2i(10, 340);
    glEnd();

    // Round Angle 2
    glColor3ub(190, 143, 69);
    glBegin(GL_TRIANGLES);
    glVertex2i(370, 332);
    glVertex2i(380, 340);
    glVertex2i(370, 340);
    glEnd();

    // Upper Left Window Bar
    if (isNight_S) {
        glColor3ub(30, 30, 30);
    } else {
        glColor3ub(0, 0, 0);
    }
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(20, 280);
    glVertex2i(80, 280);
    glVertex2i(80, 325);
    glVertex2i(20, 325);
    glEnd();

    // Upper Left Window Glass
    if (isNight_S) {
        glColor3ub(255, 220, 120);
    } else {
        glColor3ub(221, 241, 250);
    }
    glBegin(GL_QUADS);
    glVertex2i(25, 285);
    glVertex2i(75, 285);
    glVertex2i(75, 320);
    glVertex2i(25, 320);
    glEnd();

    // Upper Middle Window Bar
    if (isNight_S) {
        glColor3ub(30, 30, 30);
    } else {
        glColor3ub(0, 0, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(150, 280);
    glVertex2i(210, 280);
    glVertex2i(210, 325);
    glVertex2i(150, 325);
    glEnd();

    // Upper Middle Window Bar
    if (isNight_S) {
        glColor3ub(255, 220, 120);
    } else {
        glColor3ub(221, 241, 250);
    }
    glBegin(GL_QUADS);
    glVertex2i(155, 285);
    glVertex2i(205, 285);
    glVertex2i(205, 320);
    glVertex2i(155, 320);
    glEnd();

    // Upper Right Window Bar
    if (isNight_S) {
        glColor3ub(30, 30, 30);
    } else {
        glColor3ub(0, 0, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(280, 280);
    glVertex2i(340, 280);
    glVertex2i(340, 325);
    glVertex2i(280, 325);
    glEnd();

    // Upper Roght Window Glass
    if (isNight_S) {
        glColor3ub(255, 220, 120);
    } else {
        glColor3ub(221, 241, 250);
    }
    glBegin(GL_QUADS);
    glVertex2i(285, 285);
    glVertex2i(335, 285);
    glVertex2i(335, 320);
    glVertex2i(285, 320);
    glEnd();


    /*------------Middle Round Design-------------*/

    //1st
    glColor3ub(194, 39, 45);
    glBegin(GL_QUADS);
    glVertex2i(110, 215);
    glVertex2i(120, 215);
    glVertex2i(120, 260);
    glVertex2i(110, 260);
    glEnd();

    glColor3ub(117, 12, 16);
    glBegin(GL_TRIANGLES);
    glVertex2i(110, 215);
    glVertex2i(120, 215);
    glVertex2i(115, 210);
    glEnd();

    //2nd
    glColor3ub(230, 230, 230);
    glBegin(GL_QUADS);
    glVertex2i(120, 215);
    glVertex2i(130, 215);
    glVertex2i(130, 260);
    glVertex2i(120, 260);
    glEnd();

    glColor3ub(204, 204, 204);
    glBegin(GL_TRIANGLES);
    glVertex2i(120, 215);
    glVertex2i(130, 215);
    glVertex2i(125, 210);
    glEnd();

    //3rd
    glColor3ub(194, 39, 45);
    glBegin(GL_QUADS);
    glVertex2i(130, 215);
    glVertex2i(140, 215);
    glVertex2i(140, 260);
    glVertex2i(130, 260);
    glEnd();

    glColor3ub(117, 12, 16);
    glBegin(GL_TRIANGLES);
    glVertex2i(130, 215);
    glVertex2i(140, 215);
    glVertex2i(135, 210);
    glEnd();

    //4th
    glColor3ub(230, 230, 230);
    glBegin(GL_QUADS);
    glVertex2i(140, 215);
    glVertex2i(150, 215);
    glVertex2i(150, 260);
    glVertex2i(140, 260);
    glEnd();

    glColor3ub(204, 204, 204);
    glBegin(GL_TRIANGLES);
    glVertex2i(140, 215);
    glVertex2i(150, 215);
    glVertex2i(145, 210);
    glEnd();

    //5th
    glColor3ub(194, 39, 45);
    glBegin(GL_QUADS);
    glVertex2i(150, 215);
    glVertex2i(160, 215);
    glVertex2i(160, 260);
    glVertex2i(150, 260);
    glEnd();

    glColor3ub(117, 12, 16);
    glBegin(GL_TRIANGLES);
    glVertex2i(150, 215);
    glVertex2i(160, 215);
    glVertex2i(155, 210);
    glEnd();

    //6th
    glColor3ub(194, 39, 45);
    glBegin(GL_QUADS);
    glVertex2i(195, 215);
    glVertex2i(205, 215);
    glVertex2i(205, 260);
    glVertex2i(195, 260);
    glEnd();

    glColor3ub(117, 12, 16);
    glBegin(GL_TRIANGLES);
    glVertex2i(195, 215);
    glVertex2i(205, 215);
    glVertex2i(200, 210);
    glEnd();

    //4th
    glColor3ub(230, 230, 230);
    glBegin(GL_QUADS);
    glVertex2i(205, 215);
    glVertex2i(215, 215);
    glVertex2i(215, 260);
    glVertex2i(205, 260);
    glEnd();

    glColor3ub(204, 204, 204);
    glBegin(GL_TRIANGLES);
    glVertex2i(205, 215);
    glVertex2i(215, 215);
    glVertex2i(210, 210);
    glEnd();

    //8th
    glColor3ub(194, 39, 45);
    glBegin(GL_QUADS);
    glVertex2i(215, 215);
    glVertex2i(225, 215);
    glVertex2i(225, 260);
    glVertex2i(215, 260);
    glEnd();

    glColor3ub(117, 12, 16);
    glBegin(GL_TRIANGLES);
    glVertex2i(215, 215);
    glVertex2i(225, 215);
    glVertex2i(220, 210);
    glEnd();

    //9th
    glColor3ub(230, 230, 230);
    glBegin(GL_QUADS);
    glVertex2i(225, 215);
    glVertex2i(235, 215);
    glVertex2i(235, 260);
    glVertex2i(225, 260);
    glEnd();

    glColor3ub(204, 204, 204);
    glBegin(GL_TRIANGLES);
    glVertex2i(225, 215);
    glVertex2i(235, 215);
    glVertex2i(230, 210);
    glEnd();

    //10th
    glColor3ub(194, 39, 45);
    glBegin(GL_QUADS);
    glVertex2i(235, 215);
    glVertex2i(245, 215);
    glVertex2i(245, 260);
    glVertex2i(235, 260);
    glEnd();

    glColor3ub(117, 12, 16);
    glBegin(GL_TRIANGLES);
    glVertex2i(235, 215);
    glVertex2i(245, 215);
    glVertex2i(240, 210);
    glEnd();
}

/*---------------Shadow-------------*/

void Shade()
{

    //Shade 1
    if (isNight_S) {
        glColor3ub(50, 60, 65);
    } else {
        glColor3ub(195, 203, 200);
    }
    glBegin(GL_POLYGON);
    glVertex2i(400, 150);
    glVertex2i(470, 150);
    glVertex2i(470, 500);
    glVertex2i(460, 500);
    glVertex2i(400, 550);
    glEnd();

    //Shade 2
    if (isNight_S) {
        glColor3ub(50, 60, 65);
    } else {
        glColor3ub(195, 203, 200);
    }
    glBegin(GL_POLYGON);
    glVertex2i(480, 150);
    glVertex2i(530, 150);
    glVertex2i(530, 450);
    glVertex2i(550, 450);
    glVertex2i(480, 500);
    glEnd();


    //Shade 3 piller
    if (isNight_S) {
        glColor3ub(50, 60, 65);
    } else {
        glColor3ub(195, 203, 200);
    }
    glBegin(GL_QUADS);
    glVertex2i(540, 300);
    glVertex2i(560, 300);
    glVertex2i(560, 500);
    glVertex2i(540, 500);
    glEnd();


    //Shade 3
    if (isNight_S) {
        glColor3ub(50, 60, 65);
    } else {
        glColor3ub(195, 203, 200);
    }
    glBegin(GL_POLYGON);
    glVertex2i(560, 150);
    glVertex2i(620, 150);
    glVertex2i(620, 460);
    glVertex2i(600, 480);
    glVertex2i(600, 500);
    glVertex2i(560, 500);
    glEnd();

    //Shade 4
    if (isNight_S) {
        glColor3ub(50, 60, 65);
    } else {
        glColor3ub(195, 203, 200);
    }
    glBegin(GL_POLYGON);
    glVertex2i(560, 150);
    glVertex2i(620, 150);
    glVertex2i(620, 460);
    glVertex2i(600, 480);
    glVertex2i(600, 500);
    glVertex2i(560, 500);
    glEnd();

    //Shade 5 PILLER
    if (isNight_S) {
        glColor3ub(40, 50, 55);
    } else {
        glColor3ub(151, 163, 151);
    }
    glBegin(GL_QUADS);
    glVertex2i(640, 145);
    glVertex2i(660, 145);
    glVertex2i(660, 460);
    glVertex2i(640, 460);
    glEnd();


    //Shade 5
    if (isNight_S) {
        glColor3ub(50, 60, 65);
    } else {
        glColor3ub(195, 203, 200);
    }
    glBegin(GL_POLYGON);
    glVertex2i(660, 150);
    glVertex2i(760, 150);
    glVertex2i(760, 460);
    glVertex2i(750, 500);
    glVertex2i(700, 500);
    glVertex2i(700, 460);
    glVertex2i(660, 460);
    glEnd();

}

void School()
{
    //Body
    if (isNight_S) {
        glColor3ub(120, 65, 15);
    } else {
        glColor3ub (246, 130, 31);
    }
    glBegin(GL_QUADS);
    glVertex2i(400, 145);
    glVertex2i(700, 145);
    glVertex2i(700, 300);
    glVertex2i(400, 300);
    glEnd();

    //Roof Shade
    if (isNight_S) {
        glColor3ub(50, 50, 120);
    } else {
        glColor3ub (120, 120, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(390, 290);
    glVertex2i(710, 290);
    glVertex2i(700, 350);
    glVertex2i(400, 350);
    glEnd();

    //Roof Door Shade
    if (isNight_S) {
        glColor3ub(0, 50, 30);
    } else {
        glColor3ub(4, 77, 53);
    }
    glBegin(GL_POLYGON);
    glVertex2i(490, 305);
    glVertex2i(610, 305);
    glVertex2i(610, 315);
    glVertex2i(550, 360);
    glVertex2i(490, 315);
    glEnd();

    //Door Shade
    if (isNight_S) {
        glColor3ub(100, 75, 15);
    } else {
        glColor3ub (252, 176, 31);
    }
    glBegin(GL_POLYGON);
    glVertex2i(500, 145);
    glVertex2i(600, 145);
    glVertex2i(600, 310);
    glVertex2i(550, 330);
    glVertex2i(500, 310);
    glEnd();

    //Door Body
    if (isNight_S) {
        glColor3ub(60, 30, 35);
    } else {
        glColor3ub (96, 45, 48);
    }
    glBegin(GL_QUADS);
    glVertex2i(520, 145);
    glVertex2i(580, 145);
    glVertex2i(580, 220);
    glVertex2i(520, 220);
    glEnd();

    //Door Left Side
    if (isNight_S) {
        glColor3ub(80, 35, 30);
    } else {
        glColor3ub (119, 49, 41);
    }
    glBegin(GL_QUADS);
    glVertex2i(525, 145);
    glVertex2i(548, 145);
    glVertex2i(548, 215);
    glVertex2i(525, 215);
    glEnd();

    //Door Right Side
    if (isNight_S) {
        glColor3ub(80, 35, 30);
    } else {
        glColor3ub (119, 49, 41);
    }
    glBegin(GL_QUADS);
    glVertex2i(552, 145);
    glVertex2i(575, 145);
    glVertex2i(575, 215);
    glVertex2i(552, 215);
    glEnd();

    //Window Body
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(520, 250);
    glVertex2i(580, 250);
    glVertex2i(580, 300);
    glVertex2i(520, 300);
    glEnd();

    //Window Left Down
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(523, 255);
    glVertex2i(547, 255);
    glVertex2i(547, 275);
    glVertex2i(523, 275);
    glEnd();

    //Window Right Down
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(553, 255);
    glVertex2i(577, 255);
    glVertex2i(577, 275);
    glVertex2i(553, 275);
    glEnd();

    //Window Left Up
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(523, 280);
    glVertex2i(547, 280);
    glVertex2i(547, 295);
    glVertex2i(523, 295);
    glEnd();

    //Window Right Down
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(553, 280);
    glVertex2i(577, 280);
    glVertex2i(577, 295);
    glVertex2i(553, 295);
    glEnd();


    /*--------------Window Frame Part----------------*/

    //Window Body Left Down
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(408, 155);
    glVertex2i(442, 155);
    glVertex2i(442, 205);
    glVertex2i(408, 205);
    glEnd();

    //Window Body Right Down
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(458, 155);
    glVertex2i(492, 155);
    glVertex2i(492, 205);
    glVertex2i(458, 205);
    glEnd();

    //Window Body Left, Left Up
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(408, 220);
    glVertex2i(442, 220);
    glVertex2i(442, 270);
    glVertex2i(408, 270);
    glEnd();

    //Window Body Right, Right Up
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(458, 220);
    glVertex2i(492, 220);
    glVertex2i(492, 270);
    glVertex2i(458, 270);
    glEnd();

    //Window Body Right, Left Down
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(608, 155);
    glVertex2i(642, 155);
    glVertex2i(642, 205);
    glVertex2i(608, 205);
    glEnd();

    //Window Body Right, Right Down
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(658, 155);
    glVertex2i(692, 155);
    glVertex2i(692, 205);
    glVertex2i(658, 205);
    glEnd();

    //Window Body Left, Left Up
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(608, 220);
    glVertex2i(642, 220);
    glVertex2i(642, 270);
    glVertex2i(608, 270);
    glEnd();

    //Window Body Right, Right Up
    if (isNight_S) {
        glColor3ub(80, 80, 80);
    } else {
        glColor3ub (255, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(658, 220);
    glVertex2i(692, 220);
    glVertex2i(692, 270);
    glVertex2i(658, 270);
    glEnd();


    /*------------Glass Part-------------*/

    // Glass Left, Left Down 1
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(413, 160);
    glVertex2i(437, 160);
    glVertex2i(437, 175);
    glVertex2i(413, 175);
    glEnd();

    // Glass Left, Left Down 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(413, 185);
    glVertex2i(437, 185);
    glVertex2i(437, 200);
    glVertex2i(413, 200);
    glEnd();

    // Glass Left, Right Down 1
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(463, 160);
    glVertex2i(487, 160);
    glVertex2i(487, 175);
    glVertex2i(463, 175);
    glEnd();

    // Glass Left, Right Down 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(463, 185);
    glVertex2i(487, 185);
    glVertex2i(487, 200);
    glVertex2i(463, 200);
    glEnd();

    //Glass Left, Left Up 1
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(413, 225);
    glVertex2i(437, 225);
    glVertex2i(437, 240);
    glVertex2i(413, 240);
    glEnd();

    //Glass Left, Left Up 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(413, 250);
    glVertex2i(437, 250);
    glVertex2i(437, 265);
    glVertex2i(413, 265);
    glEnd();

    // Glass Left, Right Up 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(463, 225);
    glVertex2i(487, 225);
    glVertex2i(487, 240);
    glVertex2i(463, 240);
    glEnd();

    // Glass Left, Right Up 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(463, 250);
    glVertex2i(487, 250);
    glVertex2i(487, 265);
    glVertex2i(463, 265);
    glEnd();

    /*-------------------Glass Right Part----------------*/

    //Window Body Right, Left Down 1
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(613, 160);
    glVertex2i(637, 160);
    glVertex2i(637, 175);
    glVertex2i(613, 175);
    glEnd();

    //Window Body Right, Left Down 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(613, 185);
    glVertex2i(637, 185);
    glVertex2i(637, 200);
    glVertex2i(613, 200);
    glEnd();

    //Window Body Right, Right Down 1
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(663, 160);
    glVertex2i(687, 160);
    glVertex2i(687, 175);
    glVertex2i(663, 175);
    glEnd();

    //Window Body Right, Right Down 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(663, 185);
    glVertex2i(687, 185);
    glVertex2i(687, 200);
    glVertex2i(663, 200);
    glEnd();

    //Glass Left, Left Up 1
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(613, 225);
    glVertex2i(637, 225);
    glVertex2i(637, 240);
    glVertex2i(613, 240);
    glEnd();

    //Glass Right, Left Up 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(613, 250);
    glVertex2i(637, 250);
    glVertex2i(637, 265);
    glVertex2i(613, 265);
    glEnd();

    //Glass Right, Right Up 1
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(663, 225);
    glVertex2i(687, 225);
    glVertex2i(687, 240);
    glVertex2i(663, 240);
    glEnd();

    //Glass Right, Right Up 2
    if (isNight_S) {
        glColor3ub(70, 100, 120);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(663, 250);
    glVertex2i(687, 250);
    glVertex2i(687, 265);
    glVertex2i(663, 265);
    glEnd();

}


/*-----------------College----------------*/


void College()
{
    //Body
    if (isNight_S) {
        glColor3ub(80, 10, 15);
    } else {
        glColor3ub(160, 12, 16);
    }
    glBegin(GL_QUADS);
    glVertex2i(730, 170);
    glVertex2i(1180, 170);
    glVertex2i(1180, 320);
    glVertex2i(730, 320);
    glEnd();

    //Upper Frame 1
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub(95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(720, 310);
    glVertex2i(1190, 310);
    glVertex2i(1190, 320);
    glVertex2i(720, 320);
    glEnd();

    //Roof 1
    if (isNight_S) {
        glColor3ub(2, 15, 50);
    } else {
        glColor3ub(5, 30, 92);
    }
    glBegin(GL_QUADS);
    glVertex2i(720, 320);
    glVertex2i(1190, 320);
    glVertex2i(1110, 340);
    glVertex2i(800, 340);
    glEnd();

    //2nd Body
    if (isNight_S) {
        glColor3ub(80, 10, 15);
    } else {
        glColor3ub(160, 12, 16);
    }
    glBegin(GL_QUADS);
    glVertex2i(810, 340);
    glVertex2i(1100, 340);
    glVertex2i(1100, 400);
    glVertex2i(810, 400);
    glEnd();

    //Upper Frame 2
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub(95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(800, 390);
    glVertex2i(1110, 390);
    glVertex2i(1110, 400);
    glVertex2i(800, 400);
    glEnd();

    //Roof 2
    if (isNight_S) {
        glColor3ub(2, 15, 50);
    } else {
        glColor3ub(5, 30, 92);
    }
    glBegin(GL_QUADS);
    glVertex2i(800, 400);
    glVertex2i(1110, 400);
    glVertex2i(1050, 420);
    glVertex2i(860, 420);
    glEnd();

    // Gate
    if (isNight_S) {
        glColor3ub(180, 130, 40);
    } else {
        glColor3ub(251, 176, 59);
    }
    glBegin(GL_POLYGON);
    glVertex2i(860, 170);
    glVertex2i(1040, 170);
    glVertex2i(1040, 320);
    glVertex2i(950, 350);
    glVertex2i(860, 320);
    glEnd();




    /*----------Window Frame Left----------*/

    //Window Body Left Down
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub (95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(740, 180);
    glVertex2i(780, 180);
    glVertex2i(780, 230);
    glVertex2i(740, 230);
    glEnd();

    //Window Body Right Down
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub (95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(810, 180);
    glVertex2i(850, 180);
    glVertex2i(850, 230);
    glVertex2i(810, 230);
    glEnd();

    //Window Body Left Up
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub (95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(740, 240);
    glVertex2i(780, 240);
    glVertex2i(780, 290);
    glVertex2i(740, 290);
    glEnd();

    //Window Body Right Up
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub (95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(810, 240);
    glVertex2i(850, 240);
    glVertex2i(850, 290);
    glVertex2i(810, 290);
    glEnd();



    /*----------Window Frame Right----------*/


    //Window Body Left  Down
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub (95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(1050, 180);
    glVertex2i(1090, 180);
    glVertex2i(1090, 230);
    glVertex2i(1050, 230);
    glEnd();

    //Window Body Right Down
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub (95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(1120, 180);
    glVertex2i(1160, 180);
    glVertex2i(1160, 230);
    glVertex2i(1120, 230);
    glEnd();

    //Window Body Left Up
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub (95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(1050, 240);
    glVertex2i(1090, 240);
    glVertex2i(1090, 290);
    glVertex2i(1050, 290);
    glEnd();

    //Window Body Right Up
    if (isNight_S) {
        glColor3ub(50, 30, 30);
    } else {
        glColor3ub (95, 55, 55);
    }
    glBegin(GL_QUADS);
    glVertex2i(1120, 240);
    glVertex2i(1160, 240);
    glVertex2i(1160, 290);
    glVertex2i(1120, 290);
    glEnd();



    /*-------------Glass Part Left--------------*/


    // Glass 1
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(745, 185);
    glVertex2i(775, 185);
    glVertex2i(775, 200);
    glVertex2i(745, 200);
    glEnd();

    // Glass 2
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(745, 210);
    glVertex2i(775, 210);
    glVertex2i(775, 225);
    glVertex2i(745, 225);
    glEnd();

    // Glass 3
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(815, 185);
    glVertex2i(845, 185);
    glVertex2i(845, 200);
    glVertex2i(815, 200);
    glEnd();

    // Glass 4
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(815, 210);
    glVertex2i(845, 210);
    glVertex2i(845, 225);
    glVertex2i(815, 225);
    glEnd();

    // Glass 5
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(745, 245);
    glVertex2i(775, 245);
    glVertex2i(775, 260);
    glVertex2i(745, 260);
    glEnd();

    // Glass 6
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(745, 270);
    glVertex2i(775, 270);
    glVertex2i(775, 285);
    glVertex2i(745, 285);
    glEnd();

    // Glass 7
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(815, 245);
    glVertex2i(845, 245);
    glVertex2i(845, 260);
    glVertex2i(815, 260);
    glEnd();

    // Glass 4
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(815, 270);
    glVertex2i(845, 270);
    glVertex2i(845, 285);
    glVertex2i(815, 285);
    glEnd();

    /*-------------Glass Part Left--------------*/

    // Glass 1
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(1055, 185);
    glVertex2i(1085, 185);
    glVertex2i(1085, 200);
    glVertex2i(1055, 200);
    glEnd();

    // Glass 2
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(1055, 210);
    glVertex2i(1085, 210);
    glVertex2i(1085, 225);
    glVertex2i(1055, 225);
    glEnd();

    // Glass 3
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(1125, 185);
    glVertex2i(1155, 185);
    glVertex2i(1155, 200);
    glVertex2i(1125, 200);
    glEnd();

    // Glass 4
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(1125, 210);
    glVertex2i(1155, 210);
    glVertex2i(1155, 225);
    glVertex2i(1125, 225);
    glEnd();

    // Glass 5
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(1055, 245);
    glVertex2i(1085, 245);
    glVertex2i(1085, 260);
    glVertex2i(1055, 260);
    glEnd();

    // Glass 6
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(1055, 270);
    glVertex2i(1085, 270);
    glVertex2i(1085, 285);
    glVertex2i(1055, 285);
    glEnd();

    // Glass 7
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(1125, 245);
    glVertex2i(1155, 245);
    glVertex2i(1155, 260);
    glVertex2i(1125, 260);
    glEnd();

    // Glass 7
    if (isNight_S) {
        glColor3ub (200, 170, 50);
    } else {
        glColor3ub (127, 186, 204);
    }
    glBegin(GL_QUADS);
    glVertex2i(1125, 270);
    glVertex2i(1155, 270);
    glVertex2i(1155, 285);
    glVertex2i(1125, 285);
    glEnd();


    /*---------Door-----------*/

    //Door Body
    if (isNight_S) {
        glColor3ub(50, 20, 22);
    } else {
        glColor3ub (96, 45, 48);
    }
    glBegin(GL_QUADS);
    glVertex2i(920, 170);
    glVertex2i(980, 170);
    glVertex2i(980, 245);
    glVertex2i(920, 245);
    glEnd();

    //Door Left Side
    if (isNight_S) {
        glColor3ub(90, 40, 35);
    } else {
        glColor3ub (119, 49, 41);
    }
    glBegin(GL_QUADS);
    glVertex2i(925, 170);
    glVertex2i(948, 170);
    glVertex2i(948, 240);
    glVertex2i(925, 240);
    glEnd();

    //Door Right Side
    if (isNight_S) {
        glColor3ub(90, 40, 35);
    } else {
        glColor3ub (119, 49, 41);
    }
    glBegin(GL_QUADS);
    glVertex2i(952, 170);
    glVertex2i(975, 170);
    glVertex2i(975, 240);
    glVertex2i(952, 240);
    glEnd();


    /*----------- Stairs-----------*/

    if (isNight_S) {
        glColor3ub(40, 40, 40);
    } else {
        glColor3ub (169, 169, 169);
    }
    glBegin(GL_QUADS);
    glVertex2i(900, 160);
    glVertex2i(1000, 160);
    glVertex2i(980, 170);
    glVertex2i(920, 170);
    glEnd();

    if (isNight_S) {
        glColor3ub(40, 40, 40);
    } else {
        glColor3ub (169, 169, 169);
    }
    glBegin(GL_QUADS);
    glVertex2i(880, 150);
    glVertex2i(1020, 150);
    glVertex2i(995, 160);
    glVertex2i(905, 160);
    glEnd();

    if (isNight_S) {
        glColor3ub(40, 40, 40);
    } else {
        glColor3ub (169, 169, 169);
    }
    glBegin(GL_QUADS);
    glVertex2i(860, 140);
    glVertex2i(1040, 140);
    glVertex2i(1015, 150);
    glVertex2i(885, 150);
    glEnd();

    if (isNight_S) {
        glColor3ub(40, 40, 40);
    } else {
        glColor3ub (169, 169, 169);
    }
    glBegin(GL_QUADS);
    glVertex2i(840, 130);
    glVertex2i(1060, 130);
    glVertex2i(1035, 140);
    glVertex2i(865, 140);
    glEnd();

    if (isNight_S) {
        glColor3ub(40, 40, 40);
    } else {
        glColor3ub (169, 169, 169);
    }
    glBegin(GL_QUADS);
    glVertex2i(820, 120);
    glVertex2i(1080, 120);
    glVertex2i(1055, 130);
    glVertex2i(845, 130);
    glEnd();

}

/*---------------Tree_S--------------*/

void Tree_S()
{

    //Body
    if (isNight_S) {
        glColor3ub(50, 18, 6);
    } else {
        glColor3ub(132, 36, 12);
    }
    glBegin(GL_QUADS);
    glVertex2i(20, 120);
    glVertex2i(30, 120);
    glVertex2i(30, 150);
    glVertex2i(20, 150);
    glEnd();

    //Grass 1
    if (isNight_S) {
        glColor3ub(28, 68, 22);
    } else {
        glColor3ub(78, 148, 45);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(0, 135);
    glVertex2i(50, 140);
    glVertex2i(20, 185);
    glEnd();

    //Grass 2
    if (isNight_S) {
        glColor3ub(14, 59, 17);
    } else {
        glColor3ub(39, 118, 37);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(0, 160);
    glVertex2i(50, 160);
    glVertex2i(20, 210);
    glEnd();

    //Body
    if (isNight_S) {
        glColor3ub(50, 18, 6);
    } else {
        glColor3ub(132, 36, 12);
    }
    glBegin(GL_QUADS);
    glVertex2i(390, 120);
    glVertex2i(400, 120);
    glVertex2i(400, 150);
    glVertex2i(390, 150);
    glEnd();

    //Grass 1
    if (isNight_S) {
        glColor3ub(28, 68, 22);
    } else {
        glColor3ub(78, 148, 45);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(370, 135);
    glVertex2i(420, 140);
    glVertex2i(390, 185);
    glEnd();

    //Grass 2
    if (isNight_S) {
        glColor3ub(14, 59, 17);
    } else {
        glColor3ub(39, 118, 37);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(370, 160);
    glVertex2i(420, 160);
    glVertex2i(390, 210);
    glEnd();

    //Grass 3
    if (isNight_S) {
        glColor3ub(39, 74, 23);
    } else {
        glColor3ub(78, 148, 45);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(370, 190);
    glVertex2i(410, 190);
    glVertex2i(390, 220);
    glEnd();

    //Body
    if (isNight_S) {
        glColor3ub(50, 18, 6);
    } else {
        glColor3ub(132, 36, 12);
    }
    glBegin(GL_QUADS);
    glVertex2i(710, 120);
    glVertex2i(720, 120);
    glVertex2i(720, 150);
    glVertex2i(710, 150);
    glEnd();

    //Grass 1
    if (isNight_S) {
        glColor3ub(28, 68, 22);
    } else {
        glColor3ub(78, 148, 45);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(690, 135);
    glVertex2i(740, 140);
    glVertex2i(710, 185);
    glEnd();

    //Grass 2
    if (isNight_S) {
        glColor3ub(14, 59, 17);
    } else {
        glColor3ub(39, 118, 37);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(690, 160);
    glVertex2i(740, 160);
    glVertex2i(710, 210);
    glEnd();

    //Grass 3
    if (isNight_S) {
        glColor3ub(39, 74, 23);
    } else {
        glColor3ub(78, 148, 45);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(690, 190);
    glVertex2i(740, 190);
    glVertex2i(710, 220);
    glEnd();

    //Body
    if (isNight_S) {
        glColor3ub(50, 18, 6);
    } else {
        glColor3ub(132, 36, 12);
    }
    glBegin(GL_QUADS);
    glVertex2i(1180, 120);
    glVertex2i(1190, 120);
    glVertex2i(1190, 150);
    glVertex2i(1180, 150);
    glEnd();

    //Grass 1
    if (isNight_S) {
        glColor3ub(28, 68, 22);
    } else {
        glColor3ub(78, 148, 45);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(1160, 135);
    glVertex2i(1200, 140);
    glVertex2i(1180, 185);
    glEnd();

    //Grass 2
    if (isNight_S) {
        glColor3ub(14, 59, 17);
    } else {
        glColor3ub(39, 118, 37);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(1160, 160);
    glVertex2i(1200, 160);
    glVertex2i(1180, 210);
    glEnd();

    //Grass 3
    if (isNight_S) {
        glColor3ub(39, 74, 23);
    } else {
        glColor3ub(78, 148, 45);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(1160, 190);
    glVertex2i(1200, 190);
    glVertex2i(1180, 220);
    glEnd();

}

void BG()
{
    if (isNight_S) {
        glColor3ub(40, 60, 20);
    } else {
        glColor3ub(168, 189, 61);
    }
    glBegin(GL_QUADS);
    glVertex2i(0, 115);
    glVertex2i(1200, 115);
    glVertex2i(1200, 300);
    glVertex2i(0, 300);
    glEnd();
}

void Road_S()
{
    if (isNight_S) {
        glColor3ub(50, 50, 50);
    } else {
        glColor3ub(169, 169, 169);
    }
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, 115);
    glVertex2i(1200, 115);
    glVertex2i(1200, 0);
    glEnd();

    int dashWidth = 20; // dash measurement
    int dashHeight = 5;
    int Road_SWidth = 1200;
    int Road_SCenterY = 60;

    if (isNight_S) {
        glColor3ub(180, 180, 180);
    } else {
        glColor3ub(255, 255, 255);
    }
    for (int i = 0; i < 25; i++)
    {
        int dashX = (Road_SWidth / 25) * i;
        glBegin(GL_QUADS);
        glVertex2i(dashX, Road_SCenterY);
        glVertex2i(dashX + dashWidth, Road_SCenterY);
        glVertex2i(dashX + dashWidth, Road_SCenterY + dashHeight);
        glVertex2i(dashX, Road_SCenterY + dashHeight);
        glEnd();
    }
}

/*----------------Bus---------------*/

float bus1X = -350;
float bus2X = -1400;
float busSpeed = 2;
float wheelAngle = 0; // Wheel rotation angle
bool isMoving = true;

void update(int value) {
    if (isMoving)
    {
        bus1X += busSpeed;
        bus2X += busSpeed;
        wheelAngle -= 10; // Rotate wheels in forward direction

    }

    if (bus1X > 1800) {
        bus1X = -350;
        bus2X = -1400;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}


// Function to draw rotating wheels
void drawWheel(int cx, int cy) {
    glPushMatrix();
    glTranslatef(cx, cy, 0);
    glRotatef(wheelAngle, 0, 0, 1); // Rotate around center

    // Outer Black Wheel
    glColor3ub(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(0, 0);
    for (int j = 0; j <= 360; j += 10) {
        float angle = j * 3.14159 / 180;
        glVertex2i(cos(angle) * 20, sin(angle) * 20);
    }
    glEnd();

    // Inner White Circle
    glColor3ub(255, 255, 255);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2i(0, 0);
    for (int j = 0; j <= 360; j += 10) {
        float angle = j * 3.14159 / 180;
        glVertex2i(cos(angle) * 8, sin(angle) * 8);
    }
    glEnd();

    glPopMatrix();
}

void Bus1()
{

    glPushMatrix();
    glTranslatef(bus1X, 0, 0);


    //Bus Body
    if (isNight_S) {
        glColor3ub(100, 30, 30);
    } else {
        glColor3ub(255, 82, 75);
    }
    glBegin(GL_QUADS);
    glVertex2i(10, 30);
    glVertex2i(300, 30);
    glVertex2i(300, 110);
    glVertex2i(10, 110);
    glEnd();

    //Bus Shade
    if (isNight_S) {
        glColor3ub(0, 0, 0);
    } else {
        glColor3ub(0, 0, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(10, 70);
    glVertex2i(300, 70);
    glVertex2i(300, 110);
    glVertex2i(10, 110);
    glEnd();

    //Bus Window 1
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(15, 75);
    glVertex2i(50, 75);
    glVertex2i(50, 105);
    glVertex2i(15, 105);
    glEnd();

    //Bus Window 2
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(55, 75);
    glVertex2i(90, 75);
    glVertex2i(90, 105);
    glVertex2i(55, 105);
    glEnd();

    //Bus Window 3
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(95, 75);
    glVertex2i(130, 75);
    glVertex2i(130, 105);
    glVertex2i(95, 105);
    glEnd();

    //Bus Window 4
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(135, 75);
    glVertex2i(170, 75);
    glVertex2i(170, 105);
    glVertex2i(135, 105);
    glEnd();

    //Bus Door
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(175, 30);
    glVertex2i(210, 30);
    glVertex2i(210, 95);
    glVertex2i(175, 95);
    glEnd();

    //Bus Window 5
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(215, 75);
    glVertex2i(250, 75);
    glVertex2i(250, 105);
    glVertex2i(215, 105);
    glEnd();

    //Bus Window 6
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(255, 75);
    glVertex2i(290, 75);
    glVertex2i(290, 105);
    glVertex2i(255, 105);
    glEnd();

    //Bus Front Glass
    if (isNight_S) {
        glColor3ub(100, 30, 30);
    } else {
        glColor3ub(255, 82, 75);
    }
    glBegin(GL_QUADS);
    glVertex2i(300, 90);
    glVertex2i(315, 90);
    glVertex2i(315, 95);
    glVertex2i(300, 95);
    glEnd();

    //Bus Front Glass 2
    if (isNight_S) {
        glColor3ub(0, 0, 0);
    } else {
        glColor3ub(0, 0, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(308, 80);
    glVertex2i(315, 80);
    glVertex2i(315, 90);
    glVertex2i(308, 90);
    glEnd();

    // Wheels
    drawWheel(50, 20);
    drawWheel(250, 20);

    glPopMatrix();
}


void Bus2()
{

    glPushMatrix();
    glTranslatef(bus2X, 0, 0);


    //Bus Body
    if (isNight_S) {
        glColor3ub(25, 35, 112);
    } else {
        glColor3ub(44, 55, 145);
    }
    glBegin(GL_QUADS);
    glVertex2i(500, 30);
    glVertex2i(800, 30);
    glVertex2i(800, 110);
    glVertex2i(500, 110);
    glEnd();

    //Bus Shade
    if (isNight_S) {
        glColor3ub(0, 0, 0);
    } else {
        glColor3ub(0, 0, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(505, 70);
    glVertex2i(795, 70);
    glVertex2i(795, 105);
    glVertex2i(505, 105);
    glEnd();

    //Bus Window 1
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(510, 75);
    glVertex2i(545, 75);
    glVertex2i(545, 100);
    glVertex2i(510, 100);
    glEnd();

    //Bus Window 2
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(550, 75);
    glVertex2i(585, 75);
    glVertex2i(585, 100);
    glVertex2i(550, 100);
    glEnd();

    //Bus Window 3
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(590, 75);
    glVertex2i(625, 75);
    glVertex2i(625, 100);
    glVertex2i(590, 100);
    glEnd();

    //Bus Window 4
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(630, 75);
    glVertex2i(665, 75);
    glVertex2i(665, 100);
    glVertex2i(630, 100);
    glEnd();

    //Bus Door
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(670, 30);
    glVertex2i(705, 30);
    glVertex2i(705, 95);
    glVertex2i(670, 95);
    glEnd();

    //Bus Window 5
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(710, 75);
    glVertex2i(745, 75);
    glVertex2i(745, 100);
    glVertex2i(710, 100);
    glEnd();

    //Bus Window 6
    if (isNight_S) {
        glColor3ub(60, 90, 105);
    } else {
        glColor3ub(228, 255, 255);
    }
    glBegin(GL_QUADS);
    glVertex2i(750, 75);
    glVertex2i(785, 75);
    glVertex2i(785, 100);
    glVertex2i(750, 100);
    glEnd();

    //Bus Front Glass
    if (isNight_S) {
        glColor3ub(25, 35, 112);
    } else {
        glColor3ub(44, 55, 145);
    }
    glBegin(GL_QUADS);
    glVertex2i(800, 90);
    glVertex2i(815, 90);
    glVertex2i(815, 95);
    glVertex2i(800, 95);
    glEnd();

    //Bus Front Glass 2
    if (isNight_S) {
        glColor3ub(0, 0, 0);
    } else {
        glColor3ub(0, 0, 0);
    }
    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2i(808, 80);
    glVertex2i(815, 80);
    glVertex2i(815, 90);
    glVertex2i(808, 90);
    glEnd();


    //Wheel
    drawWheel(540, 20);
    drawWheel(740, 20);


    glPopMatrix();
}



/*-----------------Plane_S-------------------*/

float Plane_SX = 1200.0f;


void Plane_S()
{
    glPushMatrix();
    glTranslatef(Plane_SX, 0, 0);

    // Plane_S Body
    if (isNight_S) {
        glColor3ub(20, 50, 80);
    } else {
        glColor3ub(0, 102, 2);
    }
    glBegin(GL_QUADS);
    glVertex2i(325, 500);
    glVertex2i(500, 500);
    glVertex2i(465, 520);
    glVertex2i(360, 520);
    glEnd();

    // Plane_S Back Wind
    if (isNight_S) {
        glColor3ub(150, 20, 20);
    } else {
        glColor3ub(249, 4, 0);
    }
    glBegin(GL_TRIANGLES);
    glVertex2i(465, 520);
    glVertex2i(500, 500);
    glVertex2i(530, 530);
    glEnd();

    // Plane_S Down Wind
    if (isNight_S) {
        glColor3ub(150, 20, 20);
    } else {
        glColor3ub(249, 4, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(400, 480);
    glVertex2i(420, 475);
    glVertex2i(420, 500);
    glVertex2i(390, 500);
    glEnd();

    // Plane_S Up Wind
    if (isNight_S) {
        glColor3ub(150, 20, 20);
    } else {
        glColor3ub(249, 4, 0);
    }
    glBegin(GL_QUADS);
    glVertex2i(390, 520);
    glVertex2i(420, 520);
    glVertex2i(420, 545);
    glVertex2i(400, 540);
    glEnd();

    // Plane_S Glass 1
    if (isNight_S) {
        glColor3ub(180, 200, 255);
    } else {
        glColor3ub(0, 0, 254);
    }
    glBegin(GL_QUADS);
    glVertex2i(360, 507);
    glVertex2i(377, 507);
    glVertex2i(377, 512);
    glVertex2i(360, 512);
    glEnd();

    // Plane_S Glass 2
    if (isNight_S) {
        glColor3ub(180, 200, 255);
    } else {
        glColor3ub(0, 0, 254);
    }
    glBegin(GL_QUADS);
    glVertex2i(395, 507);
    glVertex2i(412, 507);
    glVertex2i(412, 512);
    glVertex2i(395, 512);
    glEnd();

    // Plane_S Glass 3
    if (isNight_S) {
        glColor3ub(180, 200, 255);
    } else {
        glColor3ub(0, 0, 254);
    }
    glBegin(GL_QUADS);
    glVertex2i(430, 507);
    glVertex2i(447, 507);
    glVertex2i(447, 512);
    glVertex2i(430, 512);
    glEnd();

    glPopMatrix();
}

// Function to update Plane_S position
void updatePlane_S(int value)
{
    Plane_SX -= 5.0f;

    if (Plane_SX < -1200)
        Plane_SX = 1200.0f;

    glutPostRedisplay();
    glutTimerFunc(20, updatePlane_S, 0);
}



/*-----------Rain_S Code------------*/
float rain_S = 0.0;
void Rain_S(int value)
{
    if (Rain_Sday_S)
    {
        glColor3ub(197, 226, 247);
        glBegin(GL_LINES);
        for (int i = 0; i < 1000; i++)  // Adjust density
        {
            int x = rand() % 1200;  // Match viewport width
            int y = rand() % 600;   // Match viewport height
            glVertex2d(x, y);
            glVertex2d(x, y - 10); // Falling effect
        }
        glEnd();
    }
}

/*-------------Display text on screen---------------*/

void drawText_S(const char* text, float x, float y) {
    glColor3ub(0, 0, 0); // Black color for text
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *text);
        text++;
    }
}

void drawText_S1 (const char* text, float x, float y) {
    glColor3ub(0, 0, 0); // Black color for text
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

void drawSecnery1()
{
    glClear(GL_COLOR_BUFFER_BIT);
    DaySky_S();
    BG();
    Sun_S();
    DayBuilding1_S();
    DayBuilding2_S();
    DayBuilding3_S();
    DayBuilding4_S();
    StationaryShop();
    Shade();
    School();
    College();
    Tree_S();
    Road_S();
    drawText_S("Stationary Shop", 140, 350);
    drawText_S1("School", 520, 230);
    drawText_S1("College", 915, 280);
    Bus1();
    Bus2();
    Plane_S();
    cloudSObj.DaycloudS();
    Rain_S(0);
    glFlush();
    glutSwapBuffers();
}


/*--------------Sani End ------------------*/





/*----------------------Ashik Start------------*/




float carX = 0;      // Starting position of the car
float busX = 0;      // Starting position of the car
float smokeX = 0;      // Starting position of the car
float cloudX = 0;      // Starting position of the car
float planeX = 0;      // Starting position of the car
float carSpeed = 0;
float busSpeed1 = 0;
float smokeSpeed = 4.0f;
float cloudSpeed = 0.0f;
float planeSpeed = 3.0f;

void drawCircle(float x, float y, float radius)
{
    glBegin(GL_POLYGON);  // Use line loop to draw the circle
    for (int i = 0; i < 360; i++)
    {
        float angle = i * 3.14159f / 180.0f; // Convert degrees to radians
        float dx = x + cos(angle) * radius;  // x coordinate of the point on the circle
        float dy = y + sin(angle) * radius;  // y coordinate of the point on the circle
        glVertex2f(dx, dy);  // Set the vertex
    }
    glEnd();
}

void smoke()
{
    glPushMatrix();
    glTranslatef(0,smokeX, 0);
    glColor3f(0.6f, 0.6f, 0.6f);

    drawCircle(640, 350, 10);
    drawCircle(640, 360, 8);
    drawCircle(640, 368, 6);
    glPopMatrix();
}

void Day_Sky()
{
    glColor3f(0.53f, 0.81f, 0.92f); // Light blue sky
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 600);
    glVertex2f(0, 600);
    glEnd();
}

void Plane()
{
    glPushMatrix();
    glTranslatef(planeX, 400,0);
    glScalef(8.0f, 8.0f,0);

    glColor3f(.8, .8, 0.8);
    glBegin(GL_POLYGON);
    glVertex2f(21, 20);
    glVertex2f(18, 19);
    glVertex2f(21, 19);
    glVertex2f(24, 19);
    glVertex2f(24, 20);
    glVertex2f(25, 21);
    glEnd();

    glColor3f(1, 1, 1);
    drawCircle(20, 19.6, 0.2);

    glColor3f(0, 0, 1);
    drawCircle(23.8, 20, 0.2);

    glColor3f(1, 0, 0);
    drawCircle(23.8, 19.5, 0.2);

    glPopMatrix();
}

void Clouds()
{
    glPushMatrix();
    glTranslatef(cloudX, 0, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(100.0f, 550.0f, 20.0f);
    drawCircle(120.0f, 540.0f, 20.0f);
    drawCircle(125.0f, 560.0f, 20.0f);
    drawCircle(150.0f, 550.0f, 20.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(200.0f, 490.0f, 20.0f);
    drawCircle(220.0f, 480.0f, 20.0f);
    drawCircle(225.0f, 500.0f, 20.0f);
    drawCircle(250.0f, 490.0f, 20.0f);
    drawCircle(255.0f, 490.0f, 20.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(400.0f, 520.0f, 20.0f);
    drawCircle(420.0f, 510.0f, 20.0f);
    drawCircle(425.0f, 530.0f, 20.0f);
    drawCircle(450.0f, 520.0f, 20.0f);
    drawCircle(455.0f, 520.0f, 20.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(500.0f, 560.0f, 20.0f);
    drawCircle(520.0f, 550.0f, 20.0f);
    drawCircle(525.0f, 570.0f, 20.0f);
    drawCircle(550.0f, 560.0f, 20.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(700.0f, 540.0f, 20.0f);
    drawCircle(720.0f, 530.0f, 20.0f);
    drawCircle(725.0f, 550.0f, 20.0f);
    drawCircle(750.0f, 540.0f, 20.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(850.0f, 520.0f, 20.0f);
    drawCircle(870.0f, 510.0f, 20.0f);
    drawCircle(875.0f, 530.0f, 20.0f);
    drawCircle(900.0f, 520.0f, 20.0f);
    drawCircle(905.0f, 520.0f, 20.0f);
    glPopMatrix();
}

void sunA()
{
    glColor3f(.882, .937, .161); //SUN
    drawCircle(1000.0f, 530.0f, 40.0f);
}

void Moon()
{
    glColor3f(.960, .941, .832); //moon
    drawCircle(1000.0f, 530.0f, 40.0f);
}

void Ground_D()
{
    glColor3f(0.360f, 0.478f, 0.470f);//Main Road
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 130);
    glVertex2f(0, 130);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);//White stripe on the road
    glBegin(GL_QUADS);
    glVertex2f(0, 63);
    glVertex2f(1200, 63);
    glVertex2f(1200, 67);
    glVertex2f(0, 67);
    glEnd();

    glColor3f(.525f, 0.525, 0.525f);//Main Sidewalk Height
    glBegin(GL_QUADS);
    glVertex2f(0, 130);
    glVertex2f(1200, 130);
    glVertex2f(1200, 136);
    glVertex2f(0, 136);
    glEnd();

    glColor3f(.647, 0.647, 0.647);// Sidewalk
    glBegin(GL_QUADS);
    glVertex2f(0, 136);
    glVertex2f(1200, 136);
    glVertex2f(1200, 160);
    glVertex2f(0, 160);
    glEnd();

    glColor3f(.537, 0.792, 0.306); //Green Ground
    glBegin(GL_QUADS);
    glVertex2f(0, 160);
    glVertex2f(1200, 160);
    glVertex2f(1200, 250);
    glVertex2f(0, 250);

    //Extended Road towards Medical College

    glColor3f(.647, 0.647, 0.647);//Sub Sidewalk left
    glBegin(GL_QUADS);
    glVertex2f(280, 136);
    glVertex2f(320, 206);
    glVertex2f(345, 206);
    glVertex2f(315, 136);
    glEnd();

    glColor3f(.525f, 0.525, 0.525f);//Sub Sidewalk shadow
    glBegin(GL_QUADS);
    glVertex2f(310, 130);
    glVertex2f(345, 206);
    glVertex2f(349, 206);
    glVertex2f(314, 130);
    glEnd();

    glColor3f(.647, 0.647, 0.647);//Sub Sidewalk right
    glBegin(GL_QUADS);
    glVertex2f(480, 136);
    glVertex2f(445, 206);
    glVertex2f(475, 206);
    glVertex2f(520, 136);

    glColor3f(.525f, 0.525, 0.525f);//Sub Sidewalk shadow
    glBegin(GL_QUADS);
    glVertex2f(480, 136);
    glVertex2f(445, 206);
    glVertex2f(442, 206);
    glVertex2f(477, 130);
    glEnd();

    glColor3f(.525f, 0.525, 0.525f);//Middle Sidewalk shadow
    glBegin(GL_QUADS);
    glVertex2f(445, 202);
    glVertex2f(442, 206);
    glVertex2f(349, 206);
    glVertex2f(345, 202);
    glEnd();

    glColor3f(.647, 0.647, 0.647);//Middle Sidewalk
    glBegin(GL_POLYGON);
    glVertex2f(320, 206);
    glVertex2f(475, 206);
    glVertex2f(470, 214);
    glVertex2f(465, 216);
    glVertex2f(330, 216);
    glVertex2f(325, 214);
    glEnd();

    glColor3f(.360f, .478f, .470f);//Extended Main Road
    glBegin(GL_QUADS);
    glVertex2f(314, 130);
    glVertex2f(347, 202);
    glVertex2f(444, 202);
    glVertex2f(478, 130);
    glEnd();


    glColor3f(1,1,1);//Extended Main Road Stripe
    glBegin(GL_QUADS);
    glVertex2f(396, 130);
    glVertex2f(396, 202);
    glVertex2f(400, 202);
    glVertex2f(400, 130);
    glEnd();
}

void Ground_N()
{
    glColor3f(0.252f, 0.334f, 0.329f);//Main Road
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 130);
    glVertex2f(0, 130);
    glEnd();

    glColor3f(0.7f, 0.7f, 0.7f);//White stripe on the road
    glBegin(GL_QUADS);
    glVertex2f(0, 63);
    glVertex2f(1200, 63);
    glVertex2f(1200, 67);
    glVertex2f(0, 67);
    glEnd();

    glColor3f(.525f, 0.525, 0.525f);//Main Sidewalk Height
    glBegin(GL_QUADS);
    glVertex2f(0, 130);
    glVertex2f(1200, 130);
    glVertex2f(1200, 136);
    glVertex2f(0, 136);
    glEnd();

    glColor3f(0.453f, 0.453f, 0.453f);// Sidewalk
    glBegin(GL_QUADS);
    glVertex2f(0, 136);
    glVertex2f(1200, 136);
    glVertex2f(1200, 160);
    glVertex2f(0, 160);
    glEnd();

    glColor3f(0.376f, 0.554f, 0.214f); //Green Ground
    glBegin(GL_QUADS);
    glVertex2f(0, 160);
    glVertex2f(1200, 160);
    glVertex2f(1200, 250);
    glVertex2f(0, 250);

    //Extended Road towards Medical College

    glColor3f(0.453f, 0.453f, 0.453f);//Sub Sidewalk left
    glBegin(GL_QUADS);
    glVertex2f(280, 136);
    glVertex2f(320, 206);
    glVertex2f(345, 206);
    glVertex2f(315, 136);
    glEnd();

    glColor3f(.525f, 0.525, 0.525f);//Sub Sidewalk shadow
    glBegin(GL_QUADS);
    glVertex2f(310, 130);
    glVertex2f(345, 206);
    glVertex2f(349, 206);
    glVertex2f(314, 130);
    glEnd();

    glColor3f(0.453f, 0.453f, 0.453f);//Sub Sidewalk right
    glBegin(GL_QUADS);
    glVertex2f(480, 136);
    glVertex2f(445, 206);
    glVertex2f(475, 206);
    glVertex2f(520, 136);

    glColor3f(.525f, 0.525, 0.525f);//Sub Sidewalk shadow
    glBegin(GL_QUADS);
    glVertex2f(480, 136);
    glVertex2f(445, 206);
    glVertex2f(442, 206);
    glVertex2f(477, 130);
    glEnd();

    glColor3f(.525f, 0.525, 0.525f);//Middle Sidewalk shadow
    glBegin(GL_QUADS);
    glVertex2f(445, 202);
    glVertex2f(442, 206);
    glVertex2f(349, 206);
    glVertex2f(345, 202);
    glEnd();

    glColor3f(0.453f, 0.453f, 0.453f);//Middle Sidewalk
    glBegin(GL_POLYGON);
    glVertex2f(320, 206);
    glVertex2f(475, 206);
    glVertex2f(470, 214);
    glVertex2f(465, 216);
    glVertex2f(330, 216);
    glVertex2f(325, 214);
    glEnd();

    glColor3f(0.252f, 0.334f, 0.329f);//Extended Main Road
    glBegin(GL_QUADS);
    glVertex2f(314, 130);
    glVertex2f(347, 202);
    glVertex2f(444, 202);
    glVertex2f(478, 130);
    glEnd();


    glColor3f(0.7,0.7,0.7);//Extended Main Road stripe
    glBegin(GL_QUADS);
    glVertex2f(396, 130);
    glVertex2f(396, 202);
    glVertex2f(400, 202);
    glVertex2f(400, 130);
    glEnd();
}

void Buildings()
{
    //Hospital

    glColor3f(.941, .941, .941);//Main building
    glBegin(GL_POLYGON);
    glVertex2f( 80, 185);
    glVertex2f( 90, 180);
    glVertex2f(170, 180);
    glVertex2f(180, 185);
    glVertex2f(180, 400);
    glVertex2f(170, 410);
    glVertex2f( 90, 410);
    glVertex2f( 80, 400);
    glEnd();

    glColor3f(.901, .901, .901);//left most Building
    glBegin(GL_QUADS);
    glVertex2f(-20, 185);
    glVertex2f( 80, 185);
    glVertex2f( 80, 355);
    glVertex2f(-20, 355);
    glEnd();

    glColor3f(.901, .901, .901);//Right most Building
    glBegin(GL_POLYGON);
    glVertex2f(180, 185);
    glVertex2f(270, 185);
    glVertex2f(270, 345);
    glVertex2f(260, 355);
    glVertex2f(180, 355);
    glEnd();

    glColor3f(.705, .705, .705);//Shadow of side building
    glBegin(GL_QUADS);
    glVertex2f(270, 185);
    glVertex2f(275, 185);
    glVertex2f(275, 337);
    glVertex2f(270, 345);
    glEnd();

    glColor3f(.909, 0.290, 0.188);//signboard
    glBegin(GL_QUADS);
    glVertex2f(110, 380);
    glVertex2f(150, 380);
    glVertex2f(150, 430);
    glVertex2f(110, 430);
    glEnd();

    glColor3f(1, 1, 1);//Plus sign
    glBegin(GL_QUADS);
    glVertex2f(127, 385);
    glVertex2f(133, 385);
    glVertex2f(133, 425);
    glVertex2f(127, 425);
    glEnd();

    glColor3f(1, 1, 1);//Plus sign
    glBegin(GL_QUADS);
    glVertex2f(115, 402);
    glVertex2f(145, 402);
    glVertex2f(145, 410);
    glVertex2f(115, 410);
    glEnd();

    glColor3f(.207, .219, .756);//Entrance
    glBegin(GL_QUADS);
    glVertex2f(110, 180);
    glVertex2f(150, 180);
    glVertex2f(150, 220);
    glVertex2f(110, 220);
    glEnd();

    glColor3f(1, 1, 1);//Entrance
    glBegin(GL_LINES);
    glVertex2f(110, 212);
    glVertex2f(150, 212);
    glVertex2f(130, 212);
    glVertex2f(130, 180);
    glEnd();

    //Hospital Windows
    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(90, 230);
    glVertex2f(170, 230);
    glVertex2f(170, 245);
    glVertex2f(90, 245);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(90, 255);
    glVertex2f(170, 255);
    glVertex2f(170, 270);
    glVertex2f(90, 270);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(90, 280);
    glVertex2f(170, 280);
    glVertex2f(170, 295);
    glVertex2f(90, 295);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(90, 305);
    glVertex2f(170, 305);
    glVertex2f(170, 320);
    glVertex2f(90, 320);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(90, 330);
    glVertex2f(170, 330);
    glVertex2f(170, 345);
    glVertex2f(90, 345);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(90, 355);
    glVertex2f(170, 355);
    glVertex2f(170, 370);
    glVertex2f(90, 370);
    glEnd();

    //second building windows

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(-20, 200);
    glVertex2f(70, 200);
    glVertex2f(70, 215);
    glVertex2f(-20, 215);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(-20, 225);
    glVertex2f(70, 225);
    glVertex2f(70, 240);
    glVertex2f(-20, 240);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(-20, 250);
    glVertex2f(70, 250);
    glVertex2f(70, 265);
    glVertex2f(-20, 265);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(-20, 275);
    glVertex2f(70, 275);
    glVertex2f(70, 290);
    glVertex2f(-20, 290);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(-20, 300);
    glVertex2f( 70, 300);
    glVertex2f( 70, 315);
    glVertex2f(-20, 315);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(-20, 325);
    glVertex2f( 70, 325);
    glVertex2f( 70, 340);
    glVertex2f(-20, 340);
    glEnd();

    //third building windows

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(190, 200);
    glVertex2f(260, 200);
    glVertex2f(260, 215);
    glVertex2f(190, 215);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(190, 225);
    glVertex2f(260, 225);
    glVertex2f(260, 240);
    glVertex2f(190, 240);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(190, 250);
    glVertex2f(260, 250);
    glVertex2f(260, 265);
    glVertex2f(190, 265);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(190, 275);
    glVertex2f(260, 275);
    glVertex2f(260, 290);
    glVertex2f(190, 290);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(190, 300);
    glVertex2f(260, 300);
    glVertex2f(260, 315);
    glVertex2f(190, 315);
    glEnd();

    glColor3f(.207, .219, .756);
    glBegin(GL_QUADS);
    glVertex2f(190, 325);
    glVertex2f(260, 325);
    glVertex2f(260, 340);
    glVertex2f(190, 340);
    glEnd();


    // Medical University

    glColor3f(1,1,1);//backward building
    glBegin(GL_POLYGON);
    glVertex2f(370+50, 230);
    glVertex2f(370+50, 415);
    glVertex2f(375+50, 420);
    glVertex2f(465+50, 420);
    glVertex2f(470+50, 415);
    glVertex2f(470+50, 230);
    glEnd();

    //windows

    glColor3f(0.656,0.796,0.839);//backward building
    glBegin(GL_POLYGON);
    glVertex2f(374+50, 240);
    glVertex2f(374+50, 411);
    glVertex2f(379+50, 416);
    glVertex2f(461+50, 416);
    glVertex2f(466+50, 411);
    glVertex2f(466+50, 240);
    glEnd();

    glColor3f(1,1,1);//backward building 2
    glBegin(GL_POLYGON);
    glVertex2f(300, 230);
    glVertex2f(300, 415);
    glVertex2f(305, 420);
    glVertex2f(395, 420);
    glVertex2f(400, 415);
    glVertex2f(400, 230);
    glEnd();

    //windows

    glColor3f(0.656,0.796,0.839);//backward building 2
    glBegin(GL_POLYGON);
    glVertex2f(304, 240);
    glVertex2f(304, 411);
    glVertex2f(309, 416);
    glVertex2f(391, 416);
    glVertex2f(396, 411);
    glVertex2f(396, 240);
    glEnd();

    glColor3f(1,1,1);//window Lines Horizontal
    glBegin(GL_LINES);
    glVertex2f(304, 260);
    glVertex2f(516, 260);
    glVertex2f(304, 280);
    glVertex2f(516, 280);
    glVertex2f(304, 300);
    glVertex2f(516, 300);
    glVertex2f(304, 320);
    glVertex2f(516, 320);
    glVertex2f(304, 340);
    glVertex2f(516, 340);
    glVertex2f(304, 360);
    glVertex2f(396, 360);
    glVertex2f(304, 380);
    glVertex2f(396, 380);
    glVertex2f(304, 400);
    glVertex2f(396, 400);
    glVertex2f(424, 400);
    glVertex2f(516, 400);
    glVertex2f(424, 380);
    glVertex2f(516, 380);
    glVertex2f(424, 360);
    glVertex2f(516, 360);
    glEnd();

    glColor3f(1,1,1);//window Lines vertical
    glBegin(GL_LINES);
    glVertex2f(309, 240);
    glVertex2f(309, 416);
    glVertex2f(329, 240);
    glVertex2f(329, 416);
    glVertex2f(349, 240);
    glVertex2f(349, 416);
    glVertex2f(369, 240);
    glVertex2f(369, 416);
    glVertex2f(389, 240);
    glVertex2f(389, 416);
    glVertex2f(429, 240);//Building on the right
    glVertex2f(429, 416);
    glVertex2f(449, 240);
    glVertex2f(449, 416);
    glVertex2f(469, 240);
    glVertex2f(469, 416);
    glVertex2f(489, 240);
    glVertex2f(489, 416);
    glVertex2f(509, 240);
    glVertex2f(509, 416);
    glEnd();

    glColor3f(1,1,1);//Forward building
    glBegin(GL_POLYGON);
    glVertex2f(320+40, 230);
    glVertex2f(320+40, 345);
    glVertex2f(325+40, 350);
    glVertex2f(415+40, 350);
    glVertex2f(420+40, 345);
    glVertex2f(420+40, 230);
    glEnd();

    //Windows

    glColor3f(0.656,0.796,0.839);
    glBegin(GL_POLYGON);
    glVertex2f(324+40, 240);
    glVertex2f(324+40, 341);
    glVertex2f(329+40, 346);
    glVertex2f(411+40, 346);
    glVertex2f(416+40, 341);
    glVertex2f(416+40, 240);
    glEnd();

    glColor3f(1,1,1);//window Lines horizontal
    glBegin(GL_LINES);
    glVertex2f(364, 260);
    glVertex2f(456, 260);
    glVertex2f(364, 280);
    glVertex2f(456, 280);
    glVertex2f(364, 300);
    glVertex2f(456, 300);
    glVertex2f(364, 320);
    glVertex2f(456, 320);
    glVertex2f(364, 340);
    glVertex2f(456, 340);
    glEnd();

    glColor3f(1,1,1);//window Lines vertical
    glBegin(GL_LINES);
    glVertex2f(369, 240);
    glVertex2f(369, 346);
    glVertex2f(389, 240);
    glVertex2f(389, 346);
    glVertex2f(409, 240);
    glVertex2f(409, 346);
    glVertex2f(429, 240);
    glVertex2f(429, 346);
    glVertex2f(449, 240);
    glVertex2f(449, 346);
    glEnd();

    //University Entrance

    glColor3f(0.773,0.800,0.769);//DOor
    glBegin(GL_POLYGON);
    glVertex2f(390, 230);
    glVertex2f(390, 265);
    glVertex2f(395, 270);
    glVertex2f(425, 270);
    glVertex2f(430, 265);
    glVertex2f(430, 230);

    glEnd();

    glColor3f(0,0,0);//DOor
    glBegin(GL_LINES);
    glVertex2f(410, 230);
    glVertex2f(410, 270);
    glEnd();

    //Restaurant

    glColor3f(0.195,0.596,0.898);
    glBegin(GL_QUADS);
    glVertex2i(570, 190);
    glVertex2i(570, 280);
    glVertex2i(680, 280);
    glVertex2i(680, 190);
    glEnd();

    glColor3f(0.085,0.411,0.710);
    glBegin(GL_QUADS);
    glVertex2i(570, 190);
    glVertex2i(570, 280);
    glVertex2i(560, 285);
    glVertex2i(560, 198);
    glEnd();

    glColor3f(0.191,0.371,0.660);
    glBegin(GL_TRIANGLES);
    glVertex2i(565, 280);
    glVertex2i(690, 280);
    glVertex2i(615, 320);
    glEnd();

    glColor3f(0.191,0.371,0.660);
    glBegin(GL_TRIANGLES);
    glVertex2i(565, 280);
    glVertex2i(615, 320);
    glVertex2i(550, 290);
    glEnd();

    //chimney
    glColor3f(0.191,0.371,0.660);
    glBegin(GL_QUADS);
    glVertex2i(635, 300);
    glVertex2i(645, 300);
    glVertex2i(645, 345);
    glVertex2i(635, 340);
    glEnd();

    //Door
    glColor3f(0.656,0.796,0.839);
    glBegin(GL_QUADS);
    glVertex2i(590, 190);
    glVertex2i(590, 250);
    glVertex2i(660, 250);
    glVertex2i(660, 190);
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2i(625, 190);
    glVertex2i(625, 250);

    glEnd();

    //Pharmacy
    glColor3f(0.295,0.796,0.773);
    glBegin(GL_QUADS);
    glVertex2i(713, 190);
    glVertex2i(713, 280);
    glVertex2i(823, 280);
    glVertex2i(823, 190);
    glEnd();

    glColor3f(0.187,0.664,0.640);
    glBegin(GL_QUADS);
    glVertex2i(713, 190);
    glVertex2i(713, 280);
    glVertex2i(703, 285);
    glVertex2i(703, 198);
    glEnd();

    glColor3f(0.281,0.488,0.570);
    glBegin(GL_QUADS);
    glVertex2i(708, 270);
    glVertex2i(710, 310);
    glVertex2i(815, 310);
    glVertex2i(830, 270);
    glEnd();

    glColor3f(0.281,0.488,0.570);
    glBegin(GL_TRIANGLES);
    glVertex2i(708, 270);
    glVertex2i(710, 310);
    glVertex2i(695, 280);
    glEnd();

    //Door
    glColor3f(0.281,0.488,0.570);
    glBegin(GL_QUADS);
    glVertex2i(738, 190);
    glVertex2i(738, 250);
    glVertex2i(800, 250);
    glVertex2i(800, 190);
    glEnd();

    glColor3f(0.656,0.796,0.839);
    glBegin(GL_QUADS);
    glVertex2i(767, 195);
    glVertex2i(767, 250);
    glVertex2i(800, 250);
    glVertex2i(800, 190);
    glEnd();

    glColor3f(0.656,0.796,0.839);
    glBegin(GL_QUADS);
    glVertex2i(738, 190);
    glVertex2i(738, 250);
    glVertex2i(765, 250);
    glVertex2i(765, 200);
    glEnd();

    //MegaMall
    glColor3f(0.773,0.800,0.769);
    glBegin(GL_QUADS);
    glVertex2i(860, 210);
    glVertex2i(860, 400);
    glVertex2i(1010, 440);
    glVertex2i(1010, 190);
    glEnd();

    glColor3f(0.801,0.802,0.807);
    glBegin(GL_QUADS);
    glVertex2i(1010, 190);
    glVertex2i(1010, 440);
    glVertex2i(1160, 400);
    glVertex2i(1160, 210);
    glEnd();

    //Entrances

    glColor3f(0.492,0.511,0.617);
    glBegin(GL_QUADS);
    glVertex2i(910, 203);
    glVertex2i(910, 240);
    glVertex2i(960, 236);
    glVertex2i(960, 196);
    glEnd();

    glColor3f(0.492,0.511,0.617);
    glBegin(GL_QUADS);
    glVertex2i(1060, 196);
    glVertex2i(1060, 236);
    glVertex2i(1110, 241);
    glVertex2i(1110, 203);
    glEnd();

    //windows
    glColor3f(0.203,0.203,0.515);
    glBegin(GL_QUADS);
    glVertex2i(865, 250);
    glVertex2i(865, 395);
    glVertex2i(1005, 430);
    glVertex2i(1005, 240);
    glEnd();

    glColor3f(0.382,0.382,0.757);
    glBegin(GL_QUADS);
    glVertex2i(1015, 240);
    glVertex2i(1015, 430);
    glVertex2i(1155, 395);
    glVertex2i(1155, 250);
    glEnd();

    //window Lines
    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(935, 244);
    glVertex2i(935, 412);
    glVertex2i(865, 322);
    glVertex2i(1005, 335);
    glEnd();

    glColor3f(1,1,1);
    glBegin(GL_LINES);
    glVertex2i(1085, 244);
    glVertex2i(1085, 412);
    glVertex2i(1155, 322);
    glVertex2i(1015, 335);
    glEnd();

}

void Buildings_N()
{
    //Hospital

    glColor3f(0.658, 0.658, 0.658); // Main building (Darker)
    glBegin(GL_POLYGON);
    glVertex2f( 80, 185);
    glVertex2f( 90, 180);
    glVertex2f(170, 180);
    glVertex2f(180, 185);
    glVertex2f(180, 400);
    glVertex2f(170, 410);
    glVertex2f( 90, 410);
    glVertex2f( 80, 400);
    glEnd();

    glColor3f(0.630, 0.630, 0.630); // left most Building (Darker)
    glBegin(GL_QUADS);
    glVertex2f(-20, 185);
    glVertex2f( 80, 185);
    glVertex2f( 80, 355);
    glVertex2f(-20, 355);
    glEnd();

    glColor3f(0.630, 0.630, 0.630); // Right most Building (Darker)
    glBegin(GL_POLYGON);
    glVertex2f(180, 185);
    glVertex2f(270, 185);
    glVertex2f(270, 345);
    glVertex2f(260, 355);
    glVertex2f(180, 355);
    glEnd();

    glColor3f(0.493, 0.493, 0.493); // Shadow of side building (Darker)
    glBegin(GL_QUADS);
    glVertex2f(270, 185);
    glVertex2f(275, 185);
    glVertex2f(275, 337);
    glVertex2f(270, 345);
    glEnd();

    glColor3f(0.636, 0.203, 0.132); // signboard (Darker)
    glBegin(GL_QUADS);
    glVertex2f(110, 380);
    glVertex2f(150, 380);
    glVertex2f(150, 430);
    glVertex2f(110, 430);
    glEnd();

    glColor3f(0.7, 0.7, 0.7); // Plus sign (Darker)
    glBegin(GL_QUADS);
    glVertex2f(127, 385);
    glVertex2f(133, 385);
    glVertex2f(133, 425);
    glVertex2f(127, 425);
    glEnd();

    glColor3f(0.7, 0.7, 0.7); // Plus sign (Darker)
    glBegin(GL_QUADS);
    glVertex2f(115, 402);
    glVertex2f(145, 402);
    glVertex2f(145, 410);
    glVertex2f(115, 410);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Entrance (Darker)
    glBegin(GL_QUADS);
    glVertex2f(110, 180);
    glVertex2f(150, 180);
    glVertex2f(150, 220);
    glVertex2f(110, 220);
    glEnd();

    glColor3f(0.7, 0.7, 0.7); // Entrance (Darker)
    glBegin(GL_LINES);
    glVertex2f(110, 212);
    glVertex2f(150, 212);
    glVertex2f(130, 212);
    glVertex2f(130, 180);
    glEnd();

//Hospital Windows
    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(90, 230);
    glVertex2f(170, 230);
    glVertex2f(170, 245);
    glVertex2f(90, 245);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(90, 255);
    glVertex2f(170, 255);
    glVertex2f(170, 270);
    glVertex2f(90, 270);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(90, 280);
    glVertex2f(170, 280);
    glVertex2f(170, 295);
    glVertex2f(90, 295);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(90, 305);
    glVertex2f(170, 305);
    glVertex2f(170, 320);
    glVertex2f(90, 320);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(90, 330);
    glVertex2f(170, 330);
    glVertex2f(170, 345);
    glVertex2f(90, 345);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(90, 355);
    glVertex2f(170, 355);
    glVertex2f(170, 370);
    glVertex2f(90, 370);
    glEnd();

//second building windows

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(-20, 200);
    glVertex2f(70, 200);
    glVertex2f(70, 215);
    glVertex2f(-20, 215);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(-20, 225);
    glVertex2f(70, 225);
    glVertex2f(70, 240);
    glVertex2f(-20, 240);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(-20, 250);
    glVertex2f(70, 250);
    glVertex2f(70, 265);
    glVertex2f(-20, 265);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(-20, 275);
    glVertex2f(70, 275);
    glVertex2f(70, 290);
    glVertex2f(-20, 290);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(-20, 300);
    glVertex2f( 70, 300);
    glVertex2f( 70, 315);
    glVertex2f(-20, 315);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(-20, 325);
    glVertex2f( 70, 325);
    glVertex2f( 70, 340);
    glVertex2f(-20, 340);
    glEnd();

//third building windows

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(190, 200);
    glVertex2f(260, 200);
    glVertex2f(260, 215);
    glVertex2f(190, 215);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(190, 225);
    glVertex2f(260, 225);
    glVertex2f(260, 240);
    glVertex2f(190, 240);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(190, 250);
    glVertex2f(260, 250);
    glVertex2f(260, 265);
    glVertex2f(190, 265);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(190, 275);
    glVertex2f(260, 275);
    glVertex2f(260, 290);
    glVertex2f(190, 290);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(190, 300);
    glVertex2f(260, 300);
    glVertex2f(260, 315);
    glVertex2f(190, 315);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Windows (Darker)
    glBegin(GL_QUADS);
    glVertex2f(190, 325);
    glVertex2f(260, 325);
    glVertex2f(260, 340);
    glVertex2f(190, 340);
    glEnd();


    // Medical University

    glColor3f(0.5, 0.5, 0.5); // backward building (Darker)
    glBegin(GL_POLYGON);
    glVertex2f(370+50, 230);
    glVertex2f(370+50, 415);
    glVertex2f(375+50, 420);
    glVertex2f(465+50, 420);
    glVertex2f(470+50, 415);
    glVertex2f(470+50, 230);
    glEnd();

// windows

    glColor3f(0.3, 0.4, 0.45); // backward building (Darker windows)
    glBegin(GL_POLYGON);
    glVertex2f(374+50, 240);
    glVertex2f(374+50, 411);
    glVertex2f(379+50, 416);
    glVertex2f(461+50, 416);
    glVertex2f(466+50, 411);
    glVertex2f(466+50, 240);
    glEnd();

    glColor3f(0.5, 0.5, 0.5); // backward building 2 (Darker)
    glBegin(GL_POLYGON);
    glVertex2f(300, 230);
    glVertex2f(300, 415);
    glVertex2f(305, 420);
    glVertex2f(395, 420);
    glVertex2f(400, 415);
    glVertex2f(400, 230);
    glEnd();

// windows

    glColor3f(0.3, 0.4, 0.45); // backward building 2 (Darker windows)
    glBegin(GL_POLYGON);
    glVertex2f(304, 240);
    glVertex2f(304, 411);
    glVertex2f(309, 416);
    glVertex2f(391, 416);
    glVertex2f(396, 411);
    glVertex2f(396, 240);
    glEnd();

    glColor3f(0.5, 0.5, 0.5); // window Lines Horizontal (Darker)
    glBegin(GL_LINES);
    glVertex2f(304, 260);
    glVertex2f(516, 260);
    glVertex2f(304, 280);
    glVertex2f(516, 280);
    glVertex2f(304, 300);
    glVertex2f(516, 300);
    glVertex2f(304, 320);
    glVertex2f(516, 320);
    glVertex2f(304, 340);
    glVertex2f(516, 340);
    glVertex2f(304, 360);
    glVertex2f(396, 360);
    glVertex2f(304, 380);
    glVertex2f(396, 380);
    glVertex2f(304, 400);
    glVertex2f(396, 400);
    glVertex2f(424, 400);
    glVertex2f(516, 400);
    glVertex2f(424, 380);
    glVertex2f(516, 380);
    glVertex2f(424, 360);
    glVertex2f(516, 360);
    glEnd();

    glColor3f(0.5, 0.5, 0.5); // window Lines vertical (Darker)
    glBegin(GL_LINES);
    glVertex2f(309, 240);
    glVertex2f(309, 416);
    glVertex2f(329, 240);
    glVertex2f(329, 416);
    glVertex2f(349, 240);
    glVertex2f(349, 416);
    glVertex2f(369, 240);
    glVertex2f(369, 416);
    glVertex2f(389, 240);
    glVertex2f(389, 416);
    glVertex2f(429, 240); // Building on the right
    glVertex2f(429, 416);
    glVertex2f(449, 240);
    glVertex2f(449, 416);
    glVertex2f(469, 240);
    glVertex2f(469, 416);
    glVertex2f(489, 240);
    glVertex2f(489, 416);
    glVertex2f(509, 240);
    glVertex2f(509, 416);
    glEnd();

    glColor3f(0.5, 0.5, 0.5); // Forward building (Darker)
    glBegin(GL_POLYGON);
    glVertex2f(320+40, 230);
    glVertex2f(320+40, 345);
    glVertex2f(325+40, 350);
    glVertex2f(415+40, 350);
    glVertex2f(420+40, 345);
    glVertex2f(420+40, 230);
    glEnd();

// Windows

    glColor3f(0.3, 0.4, 0.45); // Windows (Darker windows)
    glBegin(GL_POLYGON);
    glVertex2f(324+40, 240);
    glVertex2f(324+40, 341);
    glVertex2f(329+40, 346);
    glVertex2f(411+40, 346);
    glVertex2f(416+40, 341);
    glVertex2f(416+40, 240);
    glEnd();

    glColor3f(0.5, 0.5, 0.5); // window Lines horizontal (Darker)
    glBegin(GL_LINES);
    glVertex2f(364, 260);
    glVertex2f(456, 260);
    glVertex2f(364, 280);
    glVertex2f(456, 280);
    glVertex2f(364, 300);
    glVertex2f(456, 300);
    glVertex2f(364, 320);
    glVertex2f(456, 320);
    glVertex2f(364, 340);
    glVertex2f(456, 340);
    glEnd();

    glColor3f(0.5, 0.5, 0.5); // window Lines vertical (Darker)
    glBegin(GL_LINES);
    glVertex2f(369, 240);
    glVertex2f(369, 346);
    glVertex2f(389, 240);
    glVertex2f(389, 346);
    glVertex2f(409, 240);
    glVertex2f(409, 346);
    glVertex2f(429, 240);
    glVertex2f(429, 346);
    glVertex2f(449, 240);
    glVertex2f(449, 346);
    glEnd();

// University Entrance

    glColor3f(0.5, 0.6, 0.55); // Door (Darker)
    glBegin(GL_POLYGON);
    glVertex2f(390, 230);
    glVertex2f(390, 265);
    glVertex2f(395, 270);
    glVertex2f(425, 270);
    glVertex2f(430, 265);
    glVertex2f(430, 230);
    glEnd();

    glColor3f(0, 0, 0); // Door (Black)
    glBegin(GL_LINES);
    glVertex2f(410, 230);
    glVertex2f(410, 270);
    glEnd();

    // restaurant

    glColor3f(0.1, 0.3, 0.6); // Darker Bookstore main color
    glBegin(GL_QUADS);
    glVertex2i(570, 190);
    glVertex2i(570, 280);
    glVertex2i(680, 280);
    glVertex2i(680, 190);
    glEnd();

    glColor3f(0.05, 0.2, 0.45); // Darker Bookstore side color
    glBegin(GL_QUADS);
    glVertex2i(570, 190);
    glVertex2i(570, 280);
    glVertex2i(560, 285);
    glVertex2i(560, 198);
    glEnd();

    glColor3f(0.1, 0.2, 0.45); // Darker Bookstore roof color
    glBegin(GL_TRIANGLES);
    glVertex2i(565, 280);
    glVertex2i(690, 280);
    glVertex2i(615, 320);
    glEnd();

    glColor3f(0.1, 0.2, 0.45); // Darker Bookstore roof color (other triangle)
    glBegin(GL_TRIANGLES);
    glVertex2i(565, 280);
    glVertex2i(615, 320);
    glVertex2i(550, 290);
    glEnd();

    //chimney
    glColor3f(0.1, 0.2, 0.45);
    glBegin(GL_QUADS);
    glVertex2i(635, 300);
    glVertex2i(645, 300);
    glVertex2i(645, 345);
    glVertex2i(635, 340);
    glEnd();

// Door
    glColor3f(0.4, 0.5, 0.6); // Darker door color
    glBegin(GL_QUADS);
    glVertex2i(590, 190);
    glVertex2i(590, 250);
    glVertex2i(660, 250);
    glVertex2i(660, 190);
    glEnd();

    glColor3f(0, 0, 0); // Door line (unchanged)
    glBegin(GL_LINES);
    glVertex2i(625, 190);
    glVertex2i(625, 250);
    glEnd();

// Pharmacy

    glColor3f(0.15, 0.4, 0.35); // Darker Pharmacy main color
    glBegin(GL_QUADS);
    glVertex2i(713, 190);
    glVertex2i(713, 280);
    glVertex2i(823, 280);
    glVertex2i(823, 190);
    glEnd();

    glColor3f(0.1, 0.35, 0.32); // Darker Pharmacy side color
    glBegin(GL_QUADS);
    glVertex2i(713, 190);
    glVertex2i(713, 280);
    glVertex2i(703, 285);
    glVertex2i(703, 198);
    glEnd();

    glColor3f(0.1, 0.25, 0.3); // Darker Pharmacy upper area color
    glBegin(GL_QUADS);
    glVertex2i(708, 270);
    glVertex2i(710, 310);
    glVertex2i(815, 310);
    glVertex2i(830, 270);
    glEnd();

    glColor3f(0.1, 0.25, 0.3); // Darker Pharmacy upper area color (triangle)
    glBegin(GL_TRIANGLES);
    glVertex2i(708, 270);
    glVertex2i(710, 310);
    glVertex2i(695, 280);
    glEnd();

// Door
    glColor3f(0.1, 0.25, 0.3); // Darker door color
    glBegin(GL_QUADS);
    glVertex2i(738, 190);
    glVertex2i(738, 250);
    glVertex2i(800, 250);
    glVertex2i(800, 190);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Darker door (small section)
    glBegin(GL_QUADS);
    glVertex2i(767, 195);
    glVertex2i(767, 250);
    glVertex2i(800, 250);
    glVertex2i(800, 190);
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Darker door (small section)
    glBegin(GL_QUADS);
    glVertex2i(738, 190);
    glVertex2i(738, 250);
    glVertex2i(765, 250);
    glVertex2i(765, 200);
    glEnd();


    // MegaMall
    glColor3f(0.4, 0.4, 0.35); // Darker main MegaMall color
    glBegin(GL_QUADS);
    glVertex2i(860, 210);
    glVertex2i(860, 400);
    glVertex2i(1010, 440);
    glVertex2i(1010, 190);
    glEnd();

    glColor3f(0.35, 0.35, 0.4); // Darker secondary MegaMall color
    glBegin(GL_QUADS);
    glVertex2i(1010, 190);
    glVertex2i(1010, 440);
    glVertex2i(1160, 400);
    glVertex2i(1160, 210);
    glEnd();

// Entrances (with light inside)
    glColor3f(1.0, 0.8, 0.2); // Light yellow color for the entrance
    glBegin(GL_QUADS);
    glVertex2i(910, 203);
    glVertex2i(910, 240);
    glVertex2i(960, 236);
    glVertex2i(960, 196);
    glEnd();

    glColor3f(1.0, 0.8, 0.2); // Light yellow color for the other entrance
    glBegin(GL_QUADS);
    glVertex2i(1060, 196);
    glVertex2i(1060, 236);
    glVertex2i(1110, 241);
    glVertex2i(1110, 203);
    glEnd();

    // Windows (with light inside)
    glColor3f(1.0, 0.8, 0.2); // Light yellow color for left window
    glBegin(GL_QUADS);
    glVertex2i(865, 250);
    glVertex2i(865, 395);
    glVertex2i(1005, 430);
    glVertex2i(1005, 240);
    glEnd();

    glColor3f(1.0, 0.8, 0.2); // Light yellow color for right window
    glBegin(GL_QUADS);
    glVertex2i(1015, 240);
    glVertex2i(1015, 430);
    glVertex2i(1155, 395);
    glVertex2i(1155, 250);
    glEnd();

    // Window Lines (no change, keep them white for contrast)
    glColor3f(1, 1, 1); // Window lines in white
    glBegin(GL_LINES);
    glVertex2i(935, 244);
    glVertex2i(935, 412);
    glVertex2i(865, 322);
    glVertex2i(1005, 335);
    glEnd();

    glColor3f(1, 1, 1); // Window lines in white
    glBegin(GL_LINES);
    glVertex2i(1085, 244);
    glVertex2i(1085, 412);
    glVertex2i(1155, 322);
    glVertex2i(1015, 335);
    glEnd();

}

void Trees()
{
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(520, 190);
    glVertex2i(590, 195);
    glVertex2i(550, 230);
    glEnd();

    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(525, 212);
    glVertex2i(582, 208);
    glVertex2i(555, 237);
    glEnd();

    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(530, 230);
    glVertex2i(575, 230);
    glVertex2i(555, 255);
    glEnd();

    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(550, 175);
    glVertex2i(560, 175);
    glVertex2i(560, 193);
    glVertex2i(550, 193);
    glEnd();

    //Tree 2
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(670, 190);
    glVertex2i(740, 195);
    glVertex2i(700, 230);
    glEnd();

    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(675, 212);
    glVertex2i(732, 208);
    glVertex2i(705, 237);
    glEnd();

    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(680, 230);
    glVertex2i(725, 230);
    glVertex2i(705, 255);
    glEnd();

    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(700, 175);
    glVertex2i(710, 175);
    glVertex2i(710, 193);
    glVertex2i(700, 193);
    glEnd();

    //Tree 3
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(820, 190);
    glVertex2i(890, 195);
    glVertex2i(850, 230);
    glEnd();

    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(825, 212);
    glVertex2i(882, 208);
    glVertex2i(855, 237);
    glEnd();

    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(830, 230);
    glVertex2i(875, 230);
    glVertex2i(855, 255);
    glEnd();

    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(850, 175);
    glVertex2i(860, 175);
    glVertex2i(860, 193);
    glVertex2i(850, 193);
    glEnd();

    //Tree 4
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(170, 190);
    glVertex2i(240, 195);
    glVertex2i(200, 230);
    glEnd();

    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(175, 212);
    glVertex2i(232, 208);
    glVertex2i(205, 237);
    glEnd();

    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(180, 230);
    glVertex2i(225, 230);
    glVertex2i(205, 255);
    glEnd();

    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(200, 175);
    glVertex2i(210, 175);
    glVertex2i(210, 193);
    glVertex2i(200, 193);
    glEnd();

    //Tree 5
    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(1120, 190);
    glVertex2i(1190, 195);
    glVertex2i(1150, 230);
    glEnd();

    glColor3ub(39, 118, 37);
    glBegin(GL_TRIANGLES);
    glVertex2i(1125, 212);
    glVertex2i(1182, 208);
    glVertex2i(1155, 237);
    glEnd();

    glColor3ub(78, 148, 45);
    glBegin(GL_TRIANGLES);
    glVertex2i(1130, 230);
    glVertex2i(1175, 230);
    glVertex2i(1155, 255);
    glEnd();

    glColor3ub(119, 68, 34);
    glBegin(GL_QUADS);
    glVertex2i(1150, 175);
    glVertex2i(1160, 175);
    glVertex2i(1160, 193);
    glVertex2i(1150, 193);
    glEnd();

}

void Trees_N()
{
    // Tree 1 - Darker shades
    glColor3ub(55, 108, 34); // Darker green for the canopy
    glBegin(GL_TRIANGLES);
    glVertex2i(520, 190);
    glVertex2i(590, 195);
    glVertex2i(550, 230);
    glEnd();

    glColor3ub(28, 83, 27); // Even darker green for the second canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(525, 212);
    glVertex2i(582, 208);
    glVertex2i(555, 237);
    glEnd();

    glColor3ub(55, 108, 34); // Darker green for the third canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(530, 230);
    glVertex2i(575, 230);
    glVertex2i(555, 255);
    glEnd();

    glColor3ub(87, 47, 23); // Darker brown for the trunk
    glBegin(GL_QUADS);
    glVertex2i(550, 175);
    glVertex2i(560, 175);
    glVertex2i(560, 193);
    glVertex2i(550, 193);
    glEnd();

// Tree 2 - Darker shades
    glColor3ub(55, 108, 34); // Darker green for the canopy
    glBegin(GL_TRIANGLES);
    glVertex2i(670, 190);
    glVertex2i(740, 195);
    glVertex2i(700, 230);
    glEnd();

    glColor3ub(28, 83, 27); // Darker green for the second canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(675, 212);
    glVertex2i(732, 208);
    glVertex2i(705, 237);
    glEnd();

    glColor3ub(55, 108, 34); // Darker green for the third canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(680, 230);
    glVertex2i(725, 230);
    glVertex2i(705, 255);
    glEnd();

    glColor3ub(87, 47, 23); // Darker brown for the trunk
    glBegin(GL_QUADS);
    glVertex2i(700, 175);
    glVertex2i(710, 175);
    glVertex2i(710, 193);
    glVertex2i(700, 193);
    glEnd();

// Tree 3 - Darker shades
    glColor3ub(55, 108, 34); // Darker green for the canopy
    glBegin(GL_TRIANGLES);
    glVertex2i(820, 190);
    glVertex2i(890, 195);
    glVertex2i(850, 230);
    glEnd();

    glColor3ub(28, 83, 27); // Darker green for the second canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(825, 212);
    glVertex2i(882, 208);
    glVertex2i(855, 237);
    glEnd();

    glColor3ub(55, 108, 34); // Darker green for the third canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(830, 230);
    glVertex2i(875, 230);
    glVertex2i(855, 255);
    glEnd();

    glColor3ub(87, 47, 23); // Darker brown for the trunk
    glBegin(GL_QUADS);
    glVertex2i(850, 175);
    glVertex2i(860, 175);
    glVertex2i(860, 193);
    glVertex2i(850, 193);
    glEnd();

// Tree 4 - Darker shades
    glColor3ub(55, 108, 34); // Darker green for the canopy
    glBegin(GL_TRIANGLES);
    glVertex2i(170, 190);
    glVertex2i(240, 195);
    glVertex2i(200, 230);
    glEnd();

    glColor3ub(28, 83, 27); // Darker green for the second canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(175, 212);
    glVertex2i(232, 208);
    glVertex2i(205, 237);
    glEnd();

    glColor3ub(55, 108, 34); // Darker green for the third canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(180, 230);
    glVertex2i(225, 230);
    glVertex2i(205, 255);
    glEnd();

    glColor3ub(87, 47, 23); // Darker brown for the trunk
    glBegin(GL_QUADS);
    glVertex2i(200, 175);
    glVertex2i(210, 175);
    glVertex2i(210, 193);
    glVertex2i(200, 193);
    glEnd();

// Tree 5 - Darker shades
    glColor3ub(55, 108, 34); // Darker green for the canopy
    glBegin(GL_TRIANGLES);
    glVertex2i(1120, 190);
    glVertex2i(1190, 195);
    glVertex2i(1150, 230);
    glEnd();

    glColor3ub(28, 83, 27); // Darker green for the second canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(1125, 212);
    glVertex2i(1182, 208);
    glVertex2i(1155, 237);
    glEnd();

    glColor3ub(55, 108, 34); // Darker green for the third canopy layer
    glBegin(GL_TRIANGLES);
    glVertex2i(1130, 230);
    glVertex2i(1175, 230);
    glVertex2i(1155, 255);
    glEnd();

    glColor3ub(87, 47, 23); // Darker brown for the trunk
    glBegin(GL_QUADS);
    glVertex2i(1150, 175);
    glVertex2i(1160, 175);
    glVertex2i(1160, 193);
    glVertex2i(1150, 193);
    glEnd();

}
void Car_1()
{
    glPushMatrix();
    glTranslatef(carX, 0, 0);

    // Car Body (Blue color)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue color for the car body
    glBegin(GL_POLYGON);
    glVertex2f(210, 20);  // Bottom-left corner
    glVertex2f(350, 20);  // Bottom-right corner
    glVertex2f(350, 40);  // Slope up to the front
    glVertex2f(330, 60);  // Front-top corner
    glVertex2f(200, 60);  // Rear-top corner
    glVertex2f(200, 40);  // Slope down to the rear
    glEnd();

// Car Roof (Darker Blue)
    glColor3f(0.0f, 0.0f, 0.6f); // Darker blue for the roof
    glBegin(GL_POLYGON);
    glVertex2f(230, 60);  // Rear corner
    glVertex2f(320, 60);  // Front corner
    glVertex2f(305, 85);  // Front curve
    glVertex2f(245, 85);  // Rear curve
    glEnd();

// Windows (Silver color)
    glColor3f(0.75f, 0.75f, 0.75f); // Light silver color for windows
    glBegin(GL_QUADS);
    glVertex2f(250, 65);  // Bottom-left of window
    glVertex2f(300, 65);  // Bottom-right of window
    glVertex2f(290, 80);  // Top-right of window
    glVertex2f(260, 80);  // Top-left of window
    glEnd();

// Wheels (Black color)
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for wheels
    drawCircle(230, 20, 15); // Left wheel (center at (230, 20) with radius 15)
    drawCircle(320, 20, 15); // Right wheel (center at (320, 20) with radius 15)

// Wheel Caps (Dark Gray color)
    glColor3f(0.3f, 0.3f, 0.3f); // Dark gray color for wheel caps
    drawCircle(230, 20, 7); // Left wheel cap (center at (230, 20) with radius 7)
    drawCircle(320, 20, 7); // Right wheel cap (center at (320, 20) with radius 7)

    glPopMatrix();
}
void Car_1_N()
{
    glPushMatrix();
    glTranslatef(carX, 0, 0);
    //headlight
    glColor3f(0.8, 0.7, 0.3); // Darker silver color for windows
    glBegin(GL_TRIANGLES);
    glVertex2f(340, 45);  // Bottom-left of window
    glVertex2f(410, 25);  // Bottom-right of window
    glVertex2f(410, 55);  // Top-right of window
    //glVertex2f(260, 80);  // Top-left of window
    glEnd();
    // Car Body (Darker Blue)
    glColor3f(0.0f, 0.0f, 0.5f); // Darker blue for the car body
    glBegin(GL_POLYGON);
    glVertex2f(210, 20);  // Bottom-left corner
    glVertex2f(350, 20);  // Bottom-right corner
    glVertex2f(350, 40);  // Slope up to the front
    glVertex2f(330, 60);  // Front-top corner
    glVertex2f(200, 60);  // Rear-top corner
    glVertex2f(200, 40);  // Slope down to the rear
    glEnd();

// Car Roof (Darker Navy Blue)
    glColor3f(0.0f, 0.0f, 0.3f); // Even darker blue for the roof
    glBegin(GL_POLYGON);
    glVertex2f(230, 60);  // Rear corner
    glVertex2f(320, 60);  // Front corner
    glVertex2f(305, 85);  // Front curve
    glVertex2f(245, 85);  // Rear curve
    glEnd();

// Windows (Darker Silver)
    glColor3f(0.8, 0.7, 0.3); // Darker silver color for windows
    glBegin(GL_QUADS);
    glVertex2f(250, 65);  // Bottom-left of window
    glVertex2f(300, 65);  // Bottom-right of window
    glVertex2f(290, 80);  // Top-right of window
    glVertex2f(260, 80);  // Top-left of window
    glEnd();

// Wheels (Darker Black)
    glColor3f(0.0f, 0.0f, 0.0f); // Black color for wheels
    drawCircle(230, 20, 15);
    drawCircle(320, 20, 15);

// Wheel Caps (Darker Gray)
    glColor3f(0.2f, 0.2f, 0.2f); // Darker gray color for wheel caps
    drawCircle(230, 20, 7);
    drawCircle(320, 20, 7);
    glPopMatrix();
}
void Car_2()
{
    glPushMatrix();
    glTranslatef(busX, 0, 0);
    // Car Body (Blue color)
    glColor3f(1.0f, 1.0f, 1.0f); // Blue color for the car body
    glBegin(GL_POLYGON);
    glVertex2f(810, 90);  // Bottom-left corner
    glVertex2f(805, 120);  // Bottom-right corner
    glVertex2f(810, 165);  // Bottom-right corner
    glVertex2f(815, 170);  // Slope up to the front
    glVertex2f(990, 170);  // Slope up to the front
    glVertex2f(995, 165);  // Front-top corner
    glVertex2f(995, 95);  // Front-top corner
    glVertex2f(990, 90);  // Rear-top corner
    //glVertex2f(300, 40);  // Slope down to the rear
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black color for wheels
    drawCircle(850, 90, 15); // Left wheel (center at (230, 20) with radius 15)
    drawCircle(940, 90, 15); // Right wheel (center at (320, 20) with radius 15)

// Wheel Caps (Darker Gray)
    glColor3f(0.2f, 0.2f, 0.2f); // Darker gray color for wheel caps
    drawCircle(850, 90, 7); // Left wheel cap (center at (230, 20) with radius 7)
    drawCircle(940, 90, 7); // Right wheel cap (center at (320, 20) with radius 7)
    //Driver window
    glColor3f(0.0f, 1.0f, 1.0f); // Blue color for the car body
    glBegin(GL_POLYGON);
    glVertex2f(805, 120+5);  // Bottom-right corner
    glVertex2f(820+5, 120+5);  // Bottom-right corner
    glVertex2f(825+5, 125+5);  // Slope up to the front
    glVertex2f(825+5, 170);  // Slope up to the front
    glVertex2f(810, 170);  // Slope up to the front
    glEnd();
    //window
    glColor3f(0.0f, 1.0f, 1.0f); // Blue color for the car body
    glBegin(GL_POLYGON);
    glVertex2f(835, 120);  // Bottom-right corner
    glVertex2f(990, 120);  // Bottom-right corner
    glVertex2f(990, 160);  // Slope up to the front
    glVertex2f(985, 165);  // Slope up to the front
    glVertex2f(835, 165);  // Slope up to the front
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(865, 120);  // Bottom-right corner
    glVertex2f(865, 165);
    glVertex2f(866, 120);
    glVertex2f(866, 165);
    glVertex2f(895, 120);
    glVertex2f(895, 165);
    glVertex2f(896, 120);
    glVertex2f(896, 165);
    glVertex2f(895+30, 120);
    glVertex2f(895+30, 165);
    glVertex2f(896+30, 120);
    glVertex2f(896+30, 165);
    glVertex2f(895+60, 120);
    glVertex2f(895+60, 165);
    glVertex2f(896+60, 120);
    glVertex2f(896+60, 165);
    glEnd();

    glPopMatrix();
}
void Car_2_N()
{
    glPushMatrix();
    glTranslatef(busX, 0, 0);

    // Car Body (Blue color)
    glColor3f(.5f, 0.5f, 0.5f); // Blue color for the car body
    glBegin(GL_POLYGON);
    glVertex2f(810, 90);  // Bottom-left corner
    glVertex2f(805, 120);  // Bottom-right corner
    glVertex2f(810, 165);  // Bottom-right corner
    glVertex2f(815, 170);  // Slope up to the front
    glVertex2f(990, 170);  // Slope up to the front
    glVertex2f(995, 165);  // Front-top corner
    glVertex2f(995, 95);  // Front-top corner
    glVertex2f(990, 90);  // Rear-top corner
    //glVertex2f(300, 40);  // Slope down to the rear
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f); // Black color for wheels
    drawCircle(850, 90, 15); // Left wheel (center at (230, 20) with radius 15)
    drawCircle(940, 90, 15); // Right wheel (center at (320, 20) with radius 15)

// Wheel Caps (Darker Gray)
    glColor3f(0.2f, 0.2f, 0.2f); // Darker gray color for wheel caps
    drawCircle(850, 90, 7); // Left wheel cap (center at (230, 20) with radius 7)
    drawCircle(940, 90, 7); // Right wheel cap (center at (320, 20) with radius 7)
    //car window
    glColor3f(0.8, 0.7, 0.3); // Blue color for the car body
    glBegin(GL_POLYGON);
    glVertex2f(805, 120+5);  // Bottom-right corner
    glVertex2f(820+5, 120+5);  // Bottom-right corner
    glVertex2f(825+5, 125+5);  // Slope up to the front
    glVertex2f(825+5, 170);  // Slope up to the front
    glVertex2f(810, 170);  // Slope up to the front
    glEnd();

    glColor3f(0.8, 0.7, 0.3); // Blue color for the car body
    glBegin(GL_POLYGON);
    glVertex2f(835, 120);  // Bottom-right corner
    glVertex2f(990, 120);  // Bottom-right corner
    glVertex2f(990, 160);  // Slope up to the front
    glVertex2f(985, 165);  // Slope up to the front
    glVertex2f(835, 165);  // Slope up to the front
    glEnd();

    glColor3f(0,0,0);
    glBegin(GL_LINES);
    glVertex2f(865, 120);  // Bottom-right corner
    glVertex2f(865, 165);
    glVertex2f(866, 120);
    glVertex2f(866, 165);
    glVertex2f(895, 120);
    glVertex2f(895, 165);
    glVertex2f(896, 120);
    glVertex2f(896, 165);
    glVertex2f(895+30, 120);
    glVertex2f(895+30, 165);
    glVertex2f(896+30, 120);
    glVertex2f(896+30, 165);
    glVertex2f(895+60, 120);
    glVertex2f(895+60, 165);
    glVertex2f(896+60, 120);
    glVertex2f(896+60, 165);
    glEnd();
    glPopMatrix();
}
void Building_Shadows()
{
    //bg
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(590-10, 200);
    glVertex2f(660-10, 200);
    glVertex2f(660-10, 440-10);
    glVertex2f(590-10, 440-10);
    glEnd();
    //fw
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(590, 200);
    glVertex2f(660, 200);
    glVertex2f(660, 440);
    glVertex2f(590, 440);
    glEnd();

    //bg
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(690-10, 200);
    glVertex2f(760-10, 200);
    glVertex2f(760-10, 420-10);
    glVertex2f(690-10, 440-10);
    glEnd();

    //fw
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(690, 200);
    glVertex2f(760, 200);
    glVertex2f(760, 420);
    glVertex2f(690, 440);
    glEnd();

    //bg
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(840-10, 250);
    glVertex2f(910-10, 250);
    glVertex2f(910-10, 470-10);
    glVertex2f(840-10, 470-10);
    glEnd();


    //fw
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(840, 250);
    glVertex2f(910, 250);
    glVertex2f(910, 470);
    glVertex2f(840, 470);
    glEnd();

    //bg
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(240-10, 250);
    glVertex2f(310-10, 250);
    glVertex2f(310-10, 470-10);
    glVertex2f(240-10, 460-10);
    glEnd();

    //fw
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(240, 250);
    glVertex2f(310, 250);
    glVertex2f(310, 470);
    glVertex2f(240, 460);
    glEnd();

    //bg
    glColor3f(.392, .412, .519);
    glBegin(GL_QUADS);
    glVertex2f(340-10, 250);
    glVertex2f(410-10, 250);
    glVertex2f(410-10, 470-10);
    glVertex2f(340-10, 470-10);
    glEnd();

    //fw
    glColor3f(.808, .816, .855);
    glBegin(GL_QUADS);
    glVertex2f(340, 250);
    glVertex2f(410, 250);
    glVertex2f(410, 470);
    glVertex2f(340, 470);
    glEnd();
}

void Building_Shadows_N()
{
    // Background (Darker Shade)
    glColor3f(.2, .2, .3);  // Darker shade of blue
    glBegin(GL_QUADS);
    glVertex2f(590-10, 200);
    glVertex2f(660-10, 200);
    glVertex2f(660-10, 440-10);
    glVertex2f(590-10, 440-10);
    glEnd();

// Foreground (Darker Shade)
    glColor3f(.4, .4, .4);  // Darker grayish color
    glBegin(GL_QUADS);
    glVertex2f(590, 200);
    glVertex2f(660, 200);
    glVertex2f(660, 440);
    glVertex2f(590, 440);
    glEnd();

// Background (Darker Shade)
    glColor3f(.2, .2, .3);  // Darker shade of blue
    glBegin(GL_QUADS);
    glVertex2f(690-10, 200);
    glVertex2f(760-10, 200);
    glVertex2f(760-10, 420-10);
    glVertex2f(690-10, 440-10);
    glEnd();

// Foreground (Darker Shade)
    glColor3f(.4, .4, .4);  // Darker grayish color
    glBegin(GL_QUADS);
    glVertex2f(690, 200);
    glVertex2f(760, 200);
    glVertex2f(760, 420);
    glVertex2f(690, 440);
    glEnd();

// Background (Darker Shade)
    glColor3f(.2, .2, .3);  // Darker shade of blue
    glBegin(GL_QUADS);
    glVertex2f(840-10, 250);
    glVertex2f(910-10, 250);
    glVertex2f(910-10, 470-10);
    glVertex2f(840-10, 470-10);
    glEnd();

// Foreground (Darker Shade)
    glColor3f(.4, .4, .4);  // Darker grayish color
    glBegin(GL_QUADS);
    glVertex2f(840, 250);
    glVertex2f(910, 250);
    glVertex2f(910, 470);
    glVertex2f(840, 470);
    glEnd();

// Background (Darker Shade)
    glColor3f(.2, .2, .3);  // Darker shade of blue
    glBegin(GL_QUADS);
    glVertex2f(240-10, 250);
    glVertex2f(310-10, 250);
    glVertex2f(310-10, 470-10);
    glVertex2f(240-10, 460-10);
    glEnd();

// Foreground (Darker Shade)
    glColor3f(.4, .4, .4);  // Darker grayish color
    glBegin(GL_QUADS);
    glVertex2f(240, 250);
    glVertex2f(310, 250);
    glVertex2f(310, 470);
    glVertex2f(240, 460);
    glEnd();

// Background (Darker Shade)
    glColor3f(.2, .2, .3);  // Darker shade of blue
    glBegin(GL_QUADS);
    glVertex2f(340-10, 250);
    glVertex2f(410-10, 250);
    glVertex2f(410-10, 470-10);
    glVertex2f(340-10, 470-10);
    glEnd();

// Foreground (Darker Shade)
    glColor3f(.4, .4, .4);  // Darker grayish color
    glBegin(GL_QUADS);
    glVertex2f(340, 250);
    glVertex2f(410, 250);
    glVertex2f(410, 470);
    glVertex2f(340, 470);
    glEnd();

}
void Night_Sky()
{
    glColor3f(0.0f, 0.0f, 0.0f); // Light blue sky
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1200, 0);
    glVertex2f(1200, 600);
    glVertex2f(0, 600);
    glEnd();

    glPointSize(3.0f); // Set the size of the points to create visible stars
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);


    glVertex2i(50, 490);
    glVertex2i(140, 460);
    glVertex2i(190, 470);
    glVertex2i(240, 520);
    glVertex2i(290, 490);
    glVertex2i(340, 500);
    glVertex2i(390, 510);
    glVertex2i(440, 460);
    glVertex2i(500, 520);
    glVertex2i(550, 535);
    glVertex2i(590, 480);
    glVertex2i(640, 510);
    glVertex2i(690, 520);
    glVertex2i(740, 530);
    glVertex2i(790, 500);
    glVertex2i(840, 460);
    glVertex2i(890, 500);
    glVertex2i(940, 530);
    glVertex2i(70, 515);
    glVertex2i(170, 525);
    glVertex2i(230, 535);
    glVertex2i(300, 525);
    glVertex2i(350, 530);
    glVertex2i(410, 520);
    glVertex2i(470, 515);
    glVertex2i(530, 530);
    glVertex2i(590, 510);
    glVertex2i(640, 530);
    glVertex2i(710, 515);
    glVertex2i(760, 500);
    glVertex2i(820, 530);
    glVertex2i(890, 525);
    glVertex2i(940, 500);
    glVertex2i(990, 510);
    glVertex2i(1015, 515);
    glVertex2i(1115, 510);
    glVertex2i(1090, 495);
    glVertex2i(1105, 535);
    glVertex2i(1085, 520);
    glVertex2i(1150, 500);

    glEnd();

}

void Day_Scn()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Day_Sky();
    sunA();
    Clouds();
    Building_Shadows();
    Ground_D();
    smoke();
    Buildings();
    Trees();
    Car_2();
    Car_1();

    glutSwapBuffers();
}

void Night_Scn()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Night_Sky();
    Moon();
    Building_Shadows_N();
    Ground_N();
    Buildings_N();
    Trees_N();
    Car_2_N();
    Car_1_N();
    Plane();

    glutSwapBuffers();
}

void keypressed(int key, int x, int y)
{
    if (key == GLUT_KEY_UP) // Increase speed
    {
        carSpeed += 2.0f;
    }
    else if (key == GLUT_KEY_DOWN) // Decrease speed
    {
        carSpeed -= 2.0f;
        if (carSpeed < 0)
            carSpeed = 0;
    }

    if (key == GLUT_KEY_UP) // Increase speed
    {
        busSpeed += 2.0f;
    }
    else if (key == GLUT_KEY_DOWN) // Decrease speed
    {
        busSpeed -= 2.0f;
        if (busSpeed < 0)
            busSpeed = 0;
    }
}

void update1(int value)
{
    //car
    carX += carSpeed;

    if (carX > 1200)
        carX = -200;
    //bus
    busX -= busSpeed;

    if (busX < -1200)
        busX = 1250;

    //smoke
    smokeX += smokeSpeed;

    if (smokeX > 550)
        smokeX = -20;

    //cloud
    cloudX += cloudSpeed;

    if (cloudX > 1200)
        cloudX = -1000;

    //plane
    planeX -= planeSpeed;

    if (planeX < -200)
        planeX = 1300;

    glutPostRedisplay();
    glutTimerFunc(16, update1, 0);
}

void keyboard1(unsigned char key, int x, int y)
{

    switch (key)
    {
    case  'd':
        glutDisplayFunc(Day_Scn);
        glutKeyboardFunc(keyboard1);
        glutPostRedisplay();
        break;
    case 'D':
        glutDisplayFunc(Day_Scn);
        glutKeyboardFunc(keyboard1);
        glutPostRedisplay();
        break;
    case 'n':
        glutDisplayFunc(Night_Scn);
        glutKeyboardFunc(keyboard1);
        glutPostRedisplay();
        break;
    case  'N':
        glutDisplayFunc(Night_Scn);
        glutKeyboardFunc(keyboard1);
        glutPostRedisplay();
        break;
    }
}


/*-------------------AShik End---------------*/





/*------------Joytirmoy Start---------------*/


float ballonX = -100.0f; // Initial x position of the airplane
float ballonY = 500.0f; // Fixed y position of the airplane
float jcloudX1 = 200.0f, cloudX2 = 400.0f, cloudX3 = 800.0f; // Initial x positions of clouds
bool moveBallon = false; // Control airplane movement
bool jisNight = false; // Control day/night mode
float shootingStarX = 1300; // Start from far right
float shootingStarY = 600;  // Start from the top
bool shootingStarActive = false; // Initially inactive
float jmoonY = 300.0f; // Start from a lower position
bool jmoonMoving = false; // Control moon movement
bool jtimerRunning = false; // Prevent multiple timers
bool bankLightsOn = true; // Initially, the bank windows are lit

void jdrawSky() {
    if (jisNight) {
        glBegin(GL_QUADS);
        glColor3f(0.0f, 0.0f, 0.1f); // Dark blue sky for night
        glVertex2i(0, 300);
        glVertex2i(1200, 300);
        glVertex2i(1200, 600);
        glVertex2i(0, 600);
        glEnd();
    } else {
        glBegin(GL_QUADS);
        glColor3f(0.53, 0.81, 0.98); // Sky blue for day
        glVertex2i(0, 300);
        glVertex2i(1200, 300);
        glVertex2i(1200, 600);
        glVertex2i(0, 600);
        glEnd();
    }
}

void jdrawCircle(float cx, float cy, float radius, int num_segments, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= num_segments; ++i) {
        float angle = 2.0f * M_PI * i / num_segments;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void jdrawStars() {
    if (jisNight) {
        glColor3f(1.0f, 1.0f, 1.0f); // Pure white stars

        // Fixed star positions (X, Y)
        int starPositions[][2] = {
            {100, 500}, {250, 520}, {350, 530}, {450, 510}, {550, 490},
            {650, 480}, {750, 470}, {850, 490}, {950, 520}, {1100, 500},
            {200, 480}, {300, 450}, {400, 520}, {500, 540}, {600, 530},
            {700, 510}, {800, 550}, {900, 460}, {1000, 490}, {1150, 470},
            {120, 540}, {270, 560}, {370, 570}, {470, 550}, {570, 520},
            {670, 510}, {770, 500}, {870, 520}, {970, 550}, {1120, 530},
            {130, 480}, {280, 500}, {380, 520}, {480, 540}, {580, 510},
            {680, 550}, {780, 570}, {880, 460}, {980, 490}, {1130, 470}
        };

        int numStars = sizeof(starPositions) / sizeof(starPositions[0]);

        for (int i = 0; i < numStars; ++i) {
            glBegin(GL_POINTS);
            glVertex2i(starPositions[i][0], starPositions[i][1]);
            glEnd();
        }
    }
}

void drawShootingStar() {
    if (!shootingStarActive) return; // If not active, do nothing

    // --- Star Head ---
    glColor3f(1.0f, 1.0f, 1.0f); // Bright white star
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159 / 180;
        glVertex2f(shootingStarX + cos(angle) * 3, shootingStarY + sin(angle) * 3);
    }
    glEnd();

    // --- Star Tail ---
    glColor3f(1.0f, 1.0f, 0.7f); // Yellowish fading tail
    glBegin(GL_TRIANGLE_STRIP);
    glVertex2f(shootingStarX, shootingStarY);
    glVertex2f(shootingStarX - 10, shootingStarY - 3);
    glVertex2f(shootingStarX - 20, shootingStarY - 6);
    glVertex2f(shootingStarX - 30, shootingStarY - 9);
    glEnd();

    // --- Move Star ---
    shootingStarX -= 5.0f;  // Move left
    shootingStarY -= 2.0f;  // Move downward slightly

    // --- Reset if Out of Bounds ---
    if (shootingStarX < -50 || shootingStarY < 250) {
        shootingStarActive = false;  // Stop movement
    }
}

//moon

void jdrawMoon() {
    if (jisNight) {
        jdrawCircle(1000.0f, jmoonY, 30.0f, 100, 0.9f, 0.9f, 0.9f);
    }
}

void jdrawSun() {
    if (!jisNight) {
        jdrawCircle(1000.0f, 500.0f, 50.0f, 100, 1.0f, 0.9f, 0.0f); // Sun
    }
}

void jdrawCloud(float x, float y) {
    if (!jisNight) {
        jdrawCircle(x, y, 20.0f, 50, 1.0f, 1.0f, 1.0f);
        jdrawCircle(x + 25, y + 10, 25.0f, 50, 1.0f, 1.0f, 1.0f);
        jdrawCircle(x + 50, y, 20.0f, 50, 1.0f, 1.0f, 1.0f);
    }
}

void drawHotAirBalloon(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);

    // --- Balloon Envelope (Main Round Balloon) ---
    glColor3f(0.9f, 0.2f, 0.2f); // Red Balloon
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0, 50); // Center top of the balloon
    for (int angle = 0; angle <= 360; angle += 10) {
        float rad = angle * 3.14159 / 180.0f;
        glVertex2f(cos(rad) * 40, sin(rad) * 50 + 50);
    }
    glEnd();


    // --- Basket ---
    glColor3f(0.5f, 0.3f, 0.1f); // Brown basket
    glBegin(GL_QUADS);
    glVertex2f(-10, -50);
    glVertex2f(10, -50);
    glVertex2f(12, -40);
    glVertex2f(-12, -40);
    glEnd();

    // --- Basket Ropes ---
    glColor3f(0.4f, 0.4f, 0.4f); // Gray ropes
    glBegin(GL_LINES);

    glVertex2f(-10, -40);
    glVertex2f(-20, 10);

    glVertex2f(10, -40);
    glVertex2f(20, 10);
    glEnd();

    // --- Flame (Animated Effect) ---
    glColor3f(1.0f, 0.5f, 0.0f); // Orange flame
    glBegin(GL_TRIANGLES);
    glVertex2f(-5, -40);
    glVertex2f(5, -40);
    glVertex2f(0, -20);
    glEnd();

    glColor3f(1.0f, 1.0f, 0.0f); // Yellow inner flame
    glBegin(GL_TRIANGLES);
    glVertex2f(-3, -38);
    glVertex2f(3, -38);
    glVertex2f(0, -25);
    glEnd();

    glPopMatrix();
}

void jdrawRoad() {
    if (jisNight) {
        glColor3f(0.1f, 0.1f, 0.1f); // Darker road for night
    } else {
        glColor3f(0.2f, 0.2f, 0.2f); // Regular road for day
    }
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(1200, 0);
    glVertex2i(1200, 122);
    glVertex2i(0, 122);
    glEnd();

    // Road stripes
    glPushAttrib(GL_ENABLE_BIT);
    glLineWidth(5); // road_strip
    glLineStipple(10, 0xAAAA);
    glEnable(GL_LINE_STIPPLE);
    glColor3ub(255, 255, 255);
    glBegin(GL_LINES);
    glVertex2i(0, 58);
    glVertex2i(1190, 58);
    glEnd();
    glPopAttrib();
}

void jdrawBuilding(int x, int y, int width, int height, float r, float g, float b) {
    if (jisNight) {
        glColor3f(r * 0.5f, g * 0.5f, b * 0.5f); // Darker colors for night
    } else {
        glColor3f(r, g, b); // Regular colors for day
    }
    glBegin(GL_QUADS);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();
}

void jdrawLampPost(int x, int y, int width, int height) {
    int poleHeight = height * 0.8;  // 80% of total height for the pole
    int lampHeight = height * 0.2;  // 20% for the lamp head

    // Draw Pole (Dark Gray)
    glColor3f(0.3f, 0.3f, 0.3f); // Dark gray color for the pole
    glBegin(GL_QUADS);
    glVertex2f(x + width / 3, y);
    glVertex2f(x + 2 * width / 3, y);
    glVertex2f(x + 2 * width / 3, y + poleHeight);
    glVertex2f(x + width / 3, y + poleHeight);
    glEnd();

    // Draw Lamp Head (Top box)
    glColor3f(0.4f, 0.4f, 0.4f); // Slightly lighter gray
    glBegin(GL_QUADS);
    glVertex2f(x, y + poleHeight);
    glVertex2f(x + width, y + poleHeight);
    glVertex2f(x + width, y + poleHeight + lampHeight);
    glVertex2f(x, y + poleHeight + lampHeight);
    glEnd();

    // Draw Lamp Light (Inner glowing part)
    glColor3f(1.0f, 1.0f, 0.7f); // Yellowish light effect
    glBegin(GL_QUADS);
    glVertex2f(x + width / 4, y + poleHeight + lampHeight / 3);
    glVertex2f(x + 3 * width / 4, y + poleHeight + lampHeight / 3);
    glVertex2f(x + 3 * width / 4, y + poleHeight + 2 * lampHeight / 3);
    glVertex2f(x + width / 4, y + poleHeight + 2 * lampHeight / 3);
    glEnd();
}

void drawWindowsDay(int x, int y, int width, int height, int rows, int cols,
                   float rBorder, float gBorder, float bBorder,
                   float borderThickness, float rowGap, float colGap) {
    float totalGapWidth = (cols - 1) * colGap;
    float totalGapHeight = (rows - 1) * rowGap;
    float windowWidth = (width - totalGapWidth) / cols;
    float windowHeight = (height - totalGapHeight) / rows;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float wx = x + j * (windowWidth + colGap);
            float wy = y + i * (windowHeight + rowGap);

            // Draw Border (Main Frame)
            glColor3f(rBorder, gBorder, bBorder); // Custom border color
            glBegin(GL_QUADS);
            glVertex2f(wx, wy);
            glVertex2f(wx + windowWidth, wy);
            glVertex2f(wx + windowWidth, wy + windowHeight);
            glVertex2f(wx, wy + windowHeight);
            glEnd();

            // Draw Inner Window (Slightly Inset)
            if (!bankLightsOn) {
            glColor3f(0.0f, 0.0f, 0.3f); // Dark blue windows when lights are OFF
            } else if (jisNight) {
            glColor3f(1.0f, 1.0f, 0.5f); // Yellow light for night
            } else {
            glColor3f(0.7f, 0.9f, 1.0f); // Light blue glass effect for day
            }

            glBegin(GL_QUADS);
            glVertex2f(wx + borderThickness, wy + borderThickness);
            glVertex2f(wx + windowWidth - borderThickness, wy + borderThickness);
            glVertex2f(wx + windowWidth - borderThickness, wy + windowHeight - borderThickness);
            glVertex2f(wx + borderThickness, wy + windowHeight - borderThickness);
            glEnd();

            // Draw Shading for 3D Effect
            // Dark shading at bottom-right
            glColor3f(0.3f, 0.3f, 0.3f);
            glBegin(GL_QUADS);
            glVertex2f(wx + windowWidth - borderThickness, wy + borderThickness);
            glVertex2f(wx + windowWidth, wy);
            glVertex2f(wx + windowWidth, wy + windowHeight);
            glVertex2f(wx + windowWidth - borderThickness, wy + windowHeight - borderThickness);
            glEnd();

            // Light shading at top-left
            glColor3f(0.9f, 0.9f, 0.9f);
            glBegin(GL_QUADS);
            glVertex2f(wx, wy);
            glVertex2f(wx + windowWidth, wy);
            glVertex2f(wx + windowWidth - borderThickness, wy + borderThickness);
            glVertex2f(wx + borderThickness, wy + borderThickness);
            glEnd();
        }
    }
}

void drawText(const char* text, int x, int y, float r, float g, float b, int textSize) {
    glColor3f(r, g, b); // Custom text color
    glRasterPos2i(x, y);

    void* font;

    // Select font size based on textSize value
    if (textSize == 1)
        font = GLUT_BITMAP_HELVETICA_12; // Small
    else if (textSize == 2)
        font = GLUT_BITMAP_HELVETICA_18; // Medium (Default)
    else
        font = GLUT_BITMAP_TIMES_ROMAN_24; // Large

    // Render each character in text
    while (*text) {
        glutBitmapCharacter(font, *text);
        ++text;
    }
}


void jdrawTree(int x, int y, int width, int height, float rLeaves, float gLeaves, float bLeaves) {
    int trunkWidth = width / 4;  // Trunk is 1/4 of total width
    int trunkHeight = height * 0.3;  // Trunk takes 30% of total height
    int leavesHeight = height * 0.7; // Leaves take 70% of total height

    // --- Draw Trunk (Brown) ---
    glColor3f(0.55f, 0.27f, 0.07f); // Brown color
    glBegin(GL_QUADS);
    glVertex2f(x + width / 2 - trunkWidth / 2, y);
    glVertex2f(x + width / 2 + trunkWidth / 2, y);
    glVertex2f(x + width / 2 + trunkWidth / 2, y + trunkHeight);
    glVertex2f(x + width / 2 - trunkWidth / 2, y + trunkHeight);
    glEnd();

    // --- Draw Leaves (Customizable Canopy Color) ---
    if (jisNight) {
        glColor3f(rLeaves * 0.5f, gLeaves * 0.5f, bLeaves * 0.5f); // Darker leaves for night
    } else {
        glColor3f(rLeaves, gLeaves, bLeaves); // Regular leaves for day
    }

    float cx = x + width / 2; // Center X of the canopy
    float cy = y + trunkHeight + leavesHeight / 2; // Center Y of the canopy

    // Use multiple circles to form a natural tree shape
    int numCircles = 5;  // Number of circles in the canopy
    float offsets[5][2] = {
        {0, 0},  // Center
        {-width * 0.2f, -leavesHeight * 0.2f}, // Left-top
        {width * 0.2f, -leavesHeight * 0.2f},  // Right-top
        {-width * 0.15f, leavesHeight * 0.15f}, // Left-bottom
        {width * 0.15f, leavesHeight * 0.15f}   // Right-bottom
    };

    for (int i = 0; i < numCircles; i++) {
        float circleX = cx + offsets[i][0];
        float circleY = cy + offsets[i][1];

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(circleX, circleY);
        for (int angle = 0; angle <= 360; angle += 10) {
            float rad = angle * 3.14159 / 180;
            glVertex2f(circleX + cos(rad) * width * 0.4, circleY + sin(rad) * leavesHeight * 0.4);
        }
        glEnd();
    }
}

void displayJoyti() {
    glClear(GL_COLOR_BUFFER_BIT);

    jdrawSky();
    if (jisNight) {
        jdrawStars();
        jdrawMoon();
        drawShootingStar();
    } else {
        jdrawSun();
    }
    jdrawRoad();

    // Clouds
    if (!jisNight) {
        jdrawCloud(jcloudX1, 550);
        jdrawCloud(cloudX2, 520);
        jdrawCloud(cloudX3, 560);
    }

    // ---- Building 1 (Modern Office) ----
    jdrawBuilding(200, 180, 120, 280, 0.5f, 0.5f, 0.5f);  // Left Angle
    jdrawBuilding(220, 180, 120, 280, 0.7f, 0.7f, 0.7f);  // Main Building
    drawWindowsDay(225, 280, 110, 80, 4, 4, 0.0f, 0.0f, 0.0f, 1.5f, 4, 4);

    jdrawTree(-5, 190, 90, 130, 0.0f, 0.3f, 0.0f);

    // Bank
    jdrawBuilding(20, 150, 200, 300, 0.76f, 0.76f, 0.76f);//building left angle
    jdrawBuilding(50, 150, 200, 300, 0.88f, 0.88f, 0.88f);//main building
    // ---- Bank Gate ----
    jdrawBuilding(85, 150, 20, 30, 0.5f, 0.5f, 0.5f);  // Left pillar
    jdrawBuilding(195, 150, 20, 30, 0.5f, 0.5f, 0.5f); // Right pillar
    jdrawBuilding(85, 180, 130, 20, 0.7f, 0.7f, 0.7f); // Top horizontal beam
    drawWindowsDay(105, 150, 90, 30, 1, 2, 0.2f, 0.2f, 0.2f, 1, 0, 0); // Gate Panels
    drawWindowsDay(55, 270, 190, 100, 2, 7, 0.0f, 0.0f, 0.0f, 1, 2, 2);
    drawWindowsDay(55, 220, 190, 40, 2, 12, 0.0f, 0.0f, 0.0f, 1, 2, 2);
    jdrawCircle(150, 410, 25, 100, 0.34f, 0.52f, 0.15f);
    drawText("$", 146, 405, 1.0f, 0.843f, 0.0f, 3); // Label the bank

    jdrawTree(440, 230, 90, 130, 0.0f, 0.3f, 0.0f);

    // ---- Building 2
    jdrawBuilding(342, 140, 100, 320, 0.45f, 0.35f, 0.25f); // Left Angle
    jdrawBuilding(362, 140, 100, 320, 0.6f, 0.5f, 0.4f);  // Main Building
    drawWindowsDay(367, 280, 90, 120, 5, 3, 0.0f, 0.0f, 0.0f, 2, 3, 5);

    // ---- Building 3
    jdrawBuilding(480, 160, 140, 300, 0.2f, 0.2f, 0.3f);  // Left Angle
    jdrawBuilding(500, 160, 140, 300, 0.3f, 0.3f, 0.4f);  // Main Building
    drawWindowsDay(505, 250, 130, 150, 3, 6, 0.0f, 0.0f, 0.0f, 1, 2, 3);

    jdrawTree(740, 200, 80, 120, 0.5f, 0.5f, 0.0f);

    // ---- Building 4
    jdrawBuilding(640, 130, 110, 340, 0.5f, 0.3f, 0.3f);  // Left Angle
    jdrawBuilding(660, 130, 110, 340, 0.7f, 0.4f, 0.4f);  // Main Building
    drawWindowsDay(665, 150, 100, 300, 20, 4, 0.0f, 0.0f, 0.0f, 1.5f, 4, 4);

    // Trees
    jdrawTree(-5, 140, 90, 130, 0.0f, 0.6f, 0.0f);
    jdrawTree(230, 140, 90, 130, 0.0f, 0.6f, 0.0f);
    jdrawTree(290, 130, 80, 120, 0.2f, 0.7f, 0.2f);
    jdrawTree(460, 130, 80, 120, 0.2f, 0.7f, 0.2f);
    jdrawTree(560, 130, 80, 120, 0.0f, 0.6f, 0.0f);

    // Forrest
    jdrawTree(900, 200, 130, 180, 0.5f, 0.5f, 0.0f);
    jdrawTree(1050, 230, 140, 150, 0.2f, 0.7f, 0.2f);
    jdrawTree(800, 200, 100, 150, 0.0f, 0.3f, 0.0f);
    jdrawTree(780, 130, 80, 120, 0.0f, 0.6f, 0.0f);
    jdrawTree(850, 130, 100, 150, 0.2f, 0.7f, 0.2f);
    jdrawTree(1030, 130, 100, 150, 0.1f, 0.8f, 0.1f);
    jdrawTree(930, 130, 100, 150, 0.0f, 0.3f, 0.0f);
    jdrawTree(1090, 130, 140, 190, 0.0f, 0.3f, 0.0f);

    // Lamp posts
    for (int x = 60; x <= 1200; x += 60) {
        jdrawLampPost(x, 122, 20, 60);
    }

    // Ballon
    if (moveBallon) {
        drawHotAirBalloon(ballonX, ballonY);
    }

    glFlush();
}

void timer1(int value) {
    if (!jtimerRunning) return;

    // Move clouds
    jcloudX1 -= 2.0;
    cloudX2 -= 1.0;
    cloudX3 -= 0.5;

    if (jcloudX1 < -100.0f) jcloudX1 = 1300.0f;
    if (cloudX2 < -100.0f) cloudX2 = 1300.0f;
    if (cloudX3 < -100.0f) cloudX3 = 1300.0f;

    // Move the moon upwards
    if (jmoonMoving && jmoonY < 500.0f) {
        jmoonY += 1.0f;
        if (jmoonY >= 500.0f) {
            jmoonY = 500.0f;
            jmoonMoving = false;
        }
    }

    if (moveBallon) {
        ballonX += 1.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(30, timer1, 0);
}


/*------------Joytirmoy End-----------------*/

int currentScene=0;
void display() {
    switch (currentScene) {
        case 0:
            Day_r();
            break;
        case 1:
          Night_r();

            break;
        case 2:
            drawSecnery1();

            break;
        case 3:
            Day_Scn();
            break;
        case 4:
            Night_Scn();
            break;

        case 5:
            displayJoyti();
            break;

            }

   glutPostRedisplay();

}

void keyboardHandler(unsigned char key, int x, int y) {
    switch (key) {
        // Scene Selection (1-8)
        case '1': currentScene = 0; break;
        case '2': currentScene = 1; break;
        case '3': currentScene = 2; break;
        case '4': currentScene = 3; break;
        case '5': currentScene = 4; break;
        case '6': currentScene = 5; break;
        case '7': currentScene = 6; break;
        case '8': currentScene = 7; break;

        // Balloon Movement (B = Start, S = Stop)
        case 'B': case 'b':
            moveBallon = true;
            ballonX = -100.0f; // Reset balloon position
            if (!jtimerRunning) {
                jtimerRunning = true;
                glutTimerFunc(30, timer, 0);
            }
            break;
        case 'S': case 's':
            moveBallon = false;
            break;

        // Night Mode (N = Night, D = Day)
        case 'N': case 'n':
            jisNight = true;
            jmoonMoving = true;
            if (!jtimerRunning) {
                jtimerRunning = true;
                glutTimerFunc(30, timer1, 0);
            }
            glutPostRedisplay();
            break;
        case 'D': case 'd':
            jisNight = false;
            jmoonMoving = false;
            jmoonY = 100.0f; // Reset moon position
            glutDisplayFunc(Day_Scn);
            glutKeyboardFunc(keyboardHandler);
            glutPostRedisplay();
            break;

        // Toggle Lights (C = Toggle Bank Lights)
        case 'C': case 'c':
            bankLightsOn = !bankLightsOn;
            glutPostRedisplay();
            break;

        // Scene Switching (Day/Night)
        case 'm': case 'M':
            glutDisplayFunc(Night_Scn);
            glutKeyboardFunc(keyboardHandler);
            glutPostRedisplay();
            break;
        case 'l': case 'L':
            glutDisplayFunc(Day_Scn);
            glutKeyboardFunc(keyboardHandler);
            glutPostRedisplay();
            break;

        case 'r': case 'R':
            Rain_Sday_S = true;
            //cout << "Rain started." << endl;
            glutPostRedisplay();
            break;
        case 't': case 'T':
            Rain_Sday_S = false;
            //cout << "Rain stopped." << endl;
            glutPostRedisplay();
            break;

        // Car & Bus Movement (S = Stop, G = Go)
        case 'o': isMoving = false; break;
        case 'g': isMoving = true; break;
    }
}

// Special Keyboard Function (Arrow Keys)
void specialKeyHandler(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            carSpeed += 2.0f;
            busSpeed += 2.0f;
            break;
        case GLUT_KEY_DOWN:
            carSpeed -= 2.0f;
            busSpeed -= 2.0f;
            if (carSpeed < 0) carSpeed = 0;
            if (busSpeed < 0) busSpeed = 0;
            break;
    }
}


void displayControls() {
    cout << "=============================" << endl;
    cout << "       Controls Guide        " << endl;
    cout << "=============================" << endl;
    cout << "Mouse Controls:" << endl;
    cout << " 1st & 2nd Scenario control Rahul Dutta   Left Button Cloud Start, Right Button Cloud Stop " << endl;
    cout << " 3rd & 4th Scenario control Faysal Taher Sani   Left Button Night, Right Button Day " << endl;
    cout << "5th & 6th Scenario control SM ASHIKUL ISLAM  Left Button Cloud Stop, Right Button Cloud Move " << endl;
    cout << "7th 8th Scenario control Joytirmoy Halder Joyti  Left Button Falling Star " << endl;
    cout << "=============================" << endl;
    cout << "Keyboard Controls:" << endl;
    cout << " Rahul Dutta  R for Rain start & F Stop, " << endl;
    cout << "  Faysal Taher Sani r for rain t for stop rain, o for stop car g for start" << endl;
    cout << "  SM Ashikul Islam m for Night, L For Day, Arrow Key Car speed increase, Lower for dcrease " << endl;
    cout << " B For start Balloon & S For Stop, n Night, D for Day, C for On/OFF lights " << endl;
    cout << "=============================" << endl;
}

void mouseHandler(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        switch (button) {
            case GLUT_RIGHT_BUTTON:
                moveCloudRight = true;   // Start moving cloud
                isNight_S = false;       // Set night mode off
                cloudSpeed += 2.0f;      // Increase cloud speed
                break;

            case GLUT_LEFT_BUTTON:
                moveCloudRight = false;  // Stop moving cloud
                isNight_S = true;        // Set night mode on
                cloudSpeed = 0.0f;       // Stop cloud movement
                shootingStarActive = true; // Activate shooting star
                shootingStarX = 1300;
                shootingStarY = 600;
                break;
        }
        glutPostRedisplay();
    }
}



int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1200, 600);
    glutInitWindowPosition(100, 150);
    glutCreateWindow("A Modern Sub-City");
    glMatrixMode(GL_PROJECTION);
    myInit();
    glutDisplayFunc(display);
    glutTimerFunc(16, update, 0);
    glutTimerFunc(20, updatePlane_S, 0);
    glutTimerFunc(1, Rain, 0);
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(16, update1, 0);
    jtimerRunning = true;
    glutTimerFunc(30, timer1, 0);
    displayControls();
    glutKeyboardFunc(keyboardHandler);

    //glutKeyboardFunc(keyboard1);
    glutMouseFunc(mouseHandler);



    glutMainLoop();
}
