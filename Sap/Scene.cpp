#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "glut.h"
#include <stdio.h>
#include "Scene.h"
#include "utils.h"
#include "Board.h"
#include "Zero.h"
#include "Line.h"
#include <ctime>
#include <fstream>

namespace Sapper
{
    using namespace GraphUtils;
    using namespace std;


    Scene::Scene(float xStep, float zStep)
    {
        int res;
        int in = 0;
        this->xStep = 0.51;
        this->zStep = 0.51;

        x = -2.6;
        z = -2.6;

        for (int i = 0; i < m; i++)
        {
            z += 0.51;
            x = -2.6;
            for (int j = 0; j < n; j++)
            {
                boards[i][j] = new Board(x, 0.0, z, 0.5, 0.1, 0.5, diffGray, ambiGray, specGray);
                in++;
                x += 0.51;
            }
        }

        initialize();
    }

    Scene::~Scene()
    {

        for (int i = 0; i < shapes.size(); i++)
        {
            delete shapes[i];
        }
    }
    void Scene::clearNum(int i, int j)
    {
        for (auto& i: shapes){
    for (auto& j : shapes){
        delete j; }
    }
    }
    // ����������� ������, � ����� ������������ ��������� �����
    void Scene::resetArr()
    {
        mines = 0;
        srand(time(0));

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                int k = rand() % 10;
                if (k == 1) {
                    boards[i][j]->setState(k);
                    mines++;
                }
                else {
                    boards[i][j]->setState(0);
                }

                boards[i][j]->setFlaged(false);
                shapes.push_back(boards[j][i]);
            }

        }

        for (int i = 0; i < counter; i++) {
            shapes.pop_back();
        }
        

        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                boards[i][j]->setColors(diffGray, ambiGray, specGray);

            }
        }

        check();
        counter = 0;
    }
     
    void Scene::check() {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (boards[i][j]->getState() == 0) {
                    int n = 0;
                    if (i == 0) {
                        if (boards[i + 1][j]->getState() == 1) n++;
                        if (j != 9) {
                            if (boards[i][j + 1]->getState() == 1) n++;
                            if (boards[i + 1][j + 1]->getState() == 1) n++;
                        }
                        if (j != 0) {
                            if (boards[i + 1][j - 1]->getState() == 1) n++;
                            if (boards[i][j - 1]->getState() == 1) n++;
                        }
                    }

                    if (i > 0 && i < 9) {
                        if (boards[i + 1][j]->getState() == 1) n++;
                        if (boards[i - 1][j]->getState() == 1) n++;
                        if (j != 0) {
                            if (boards[i][j - 1]->getState() == 1) n++;
                            if (boards[i + 1][j - 1]->getState() == 1) n++;
                            if (boards[i - 1][j - 1]->getState() == 1) n++;
                        }
                        if (j != 9) {
                            if (boards[i + 1][j + 1]->getState() == 1) n++;
                            if (boards[i - 1][j + 1]->getState() == 1) n++;
                            if (boards[i][j + 1]->getState() == 1) n++;
                        }
                    }


                    if (i == 9) {

                        if (boards[i - 1][j]->getState() == 1) n++;
                        if (j != 0) {
                            if (boards[i][j - 1]->getState() == 1) n++;
                            if (boards[i - 1][j - 1]->getState() == 1) n++;
                        }
                        if (j != 9) {
                            if (boards[i - 1][j + 1]->getState() == 1) n++;
                            if (boards[i][j + 1]->getState() == 1) n++;
                        }
                    }



                    boards[i][j]->setNum(n);


                }

            }
        }
    }

    // ������������� ������� ������ fields � ���������� x
    float Scene::allocX(int i)
    {
        return  xStep * i - (N - 1) * xStep / 2 - 0.31;
    }

    // ������������� ������� ������ fields � ���������� z
    float Scene::allocZ(int i)
    {
        return  zStep * i - (M - 1) * zStep / 2 + 0.21;
    }

    void Scene::Logic(int j, int i)
    {
        if (!boards[i][j]->getFlaged()) {
            if (boards[i][j]->getState() == 0) {

                if (boards[i][j]->getNum() == 0)
                {
                    boards[i][j]->setColors(diffWhite, ambiWhite, specWhite);
                    numbers.push_back(new Zero (boards[i][j]->getXCenter(),
                        boards[i][j]->getYCenter()+0.0001,
                        boards[i][j]->getZCenter(),
                        boards[i][j]->getXSize(),
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize(),
                        diffViolet,
                        ambiViolet,
                        specViolet,
                        0.1));
                    counter++;
                }

                if (boards[i][j]->getNum() == 1) {
                    boards[i][j]->setColors(diffLightBlue, ambiLightBlue, specLightBlue);
                    numbers.push_back(new Line (boards[i][j]->getXCenter(),
                        boards[i][j]->getYCenter() + 0.01,
                        boards[i][j]->getZCenter()-0.02,
                        boards[i][j]->getXSize()-0.25,
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize()-0.48,
                        diffViolet,
                        ambiViolet,
                        specViolet
                        ));
                    counter++;
                }

                if (boards[i][j]->getNum() == 2) {
                    boards[i][j]->setColors(diffBlue, ambiBlue, specBlue);
                    numbers.push_back(new Line(boards[i][j]->getXCenter()-0.05,
                        boards[i][j]->getYCenter() + 0.01,
                        boards[i][j]->getZCenter() - 0.02,
                        boards[i][j]->getXSize() - 0.25,
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize() - 0.48,
                        diffViolet,
                        ambiViolet,
                        specViolet
                    ));
                    numbers.push_back(new Line(boards[i][j]->getXCenter()+0.05,
                        boards[i][j]->getYCenter() + 0.01,
                        boards[i][j]->getZCenter() - 0.02,
                        boards[i][j]->getXSize() - 0.25,
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize() - 0.48,
                        diffViolet,
                        ambiViolet,
                        specViolet
                    ));
                    counter+=2;
                }



                if (boards[i][j]->getNum() == 3) {
                    boards[i][j]->setColors(diffOrange, ambiOrange, specOrange);
                    numbers.push_back(new Line(boards[i][j]->getXCenter() - 0.08,
                        boards[i][j]->getYCenter() + 0.01,
                        boards[i][j]->getZCenter() - 0.02,
                        boards[i][j]->getXSize() - 0.25,
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize() - 0.48,
                        diffViolet,
                        ambiViolet,
                        specViolet
                    ));
                    numbers.push_back(new Line(boards[i][j]->getXCenter(),
                        boards[i][j]->getYCenter() + 0.01,
                        boards[i][j]->getZCenter() - 0.02,
                        boards[i][j]->getXSize() - 0.25,
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize() - 0.48,
                        diffViolet,
                        ambiViolet,
                        specViolet
                    ));
                    numbers.push_back(new Line(boards[i][j]->getXCenter() + 0.08,
                        boards[i][j]->getYCenter() + 0.01,
                        boards[i][j]->getZCenter() - 0.02,
                        boards[i][j]->getXSize() - 0.25,
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize() - 0.48,
                        diffViolet,
                        ambiViolet,
                        specViolet
                    ));
                    counter+=3;
                }

                if (boards[i][j]->getNum() == 4) {
                    boards[i][j]->setColors(diffViolet, ambiViolet, specViolet);
                    numbers.push_back(new Line(boards[i][j]->getXCenter() - 0.1,
                        boards[i][j]->getYCenter() + 0.01,
                        boards[i][j]->getZCenter() - 0.02,
                        boards[i][j]->getXSize() - 0.25,
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize() - 0.48,
                        diffViolet,
                        ambiViolet,
                        specViolet
                    ));
                    numbers.push_back(new Line2(boards[i][j]->getXCenter() + 0.03,
                        boards[i][j]->getYCenter() + 0.01,
                        boards[i][j]->getZCenter() - 0.02,
                        boards[i][j]->getXSize() - 0.25,
                        boards[i][j]->getYSize(),
                        boards[i][j]->getZSize() - 0.48,
                        diffViolet,
                        ambiViolet,
                        specViolet
                    ));
                    counter+=2;
                }

            }
            if (boards[i][j]->getState() == 1) {
                for (int in = 0; in < 10; in++)
                    for (int jn = 0; jn < 10; jn++) {
                        if (boards[in][jn]->getState() == 1)
                            boards[in][jn]->setColors(diffRed, ambiRed, specRed);
                    }
                finish = true;
            }
        }
    }

    void Scene::Flag(int j, int i) {
        if (boards[i][j]->getFlaged()) {
            flags--;
            boards[i][j]->setFlaged(false);
            boards[i][j]->setColors(diffGray, ambiGray, specGray);
            if (boards[i][j]->getState() == 1) {
                rgh--;
            }
        }
        else {
            flags++;
            boards[i][j]->setColors(diffYellow, ambiYellow, specYellow);


            boards[i][j]->setFlaged(true);
            if (boards[i][j]->getState() == 1) {
                rgh++;

                if (rgh == mines) {
                    finish = true;


                    if (timel <= res) {
                        res = timel;
                        std::ofstream outfile("res.txt");
                        outfile << time;
                    }
                }

                std::cout << "  " << rgh << "  " << mines;
            }
        }


    }
        
        


    
    void Scene::initialize()
    {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_ACCUM_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);

        resetArr();
        flags = 0; 
        rgh = 0;
        /*for (int i = 0; i < numbers.size(); i++)
        {
            int iter = i;
            numbers.erase(numbers.begin() + iter);
        }*/
        numbers.clear();

        GraphUtils::shuffle((int*)fields, (M - 1) * N);

        std::ifstream inFile("res.txt");
        inFile >> res;

        counter = 0;
        distZ = -6;
        angleX = 0;
        angleY = 90;
        timel = 0;
        finish = false;

    }

    
    bool Scene::findNearest(int x, int y, int& x1, int& z1)
    {
        int viewport[4];
        int iMin = -1, jMin = -1;
        double mvMatrix[16], projMatrix[16];
        double minDist = 2000;

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {

                
                double wx = allocX(j);
                double wy = 0.1;
                double wz = allocZ(i);

                // ���������� ����� viewport �������� ������� ���������:
                glGetIntegerv(GL_VIEWPORT, viewport);

                // ���������� ������ ��������� ���������:
                glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
                glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

                // ����� x, y, z ����������, �� �����������:
                double dx, dy, dz;

                // �������� ���������� �����, �� ��� ������������ �������� ��������:
                gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
                dy = viewport[3] - dy - 1; // dy ��������� ������������
                double d = (x - dx) * (x - dx) + (y - dy) * (y - dy); 
                if (d < minDist) 
                {
                    minDist = d;
                    iMin = i;
                    jMin = j;
                }
            }
        }
        if (minDist < 1000) 
        {
            x1 = jMin;
            z1 = iMin;
            return true;
        }
        else
        {
            return false;
        }
    }

    // ���������� ��䳿, ���'����� � �������������� ����
    void Scene::on_paint()
    {
        char text[128]; // ����� �������, 
                        // ���������� ������ ������� �������� �� ����� ���:
        if (finish)
        {
            sprintf(text, "Game over. Time: %d sec.   F2 - Restart game   Esc - Exit  Best: %d", timel, res);

        }
        else
        {
            sprintf(text, "F2 - Restart game   Esc - Exit  Time: %d sec. Best: %d   Flags left: %i", timel, res, mines - flags);
        }
        // ������������ ������� ��������� ����, ��� ���� �������� ��� ����:
        glViewport(0, 0, width, height);

        // ���������� ��������� �������� � ������� �����:
        float lightAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f }; // ���� �������� ��������� 
        float lightDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // ���� ��������� ��������� 
        float lightSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };// ���� ������������ �����������
        float lightPosition[] = { 1.0f, 1.0f, 1.0f, 0.0f };// ������������ ������� �����

        // ������������ ��������� ������� �����:
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

        // ��������� ��������� ���� ��� ��������:
        if (finish)
        {
            glClearColor(0, 0.7, 0.7, 0);
        }
        else
        {
            glClearColor(0, 0.5, 0.5, 0);
        }

        // ������� ������:
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

       
        glOrtho(0, 1, 0, 1, -1, 1);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glColor3f(1, 1, 0); // ������ �����
        drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
        glPopMatrix();

        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        
        gluPerspective(60, width / height, 1, 100);

        // �������� ����� ������ � ������� ��������:
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, distZ);	// ������ � ������� ��������� ��������� �� distZ, 

        glRotatef(angleX, 0.0f, 1.0f, 0.0f);  // ���� ���������� �� �� Oy
        glRotatef(angleY, 1.0f, 0.0f, 0.0f);  // ���� ���������� �� �� Ox
        glEnable(GL_DEPTH_TEST);	// �������� ����� ������� (��� �������� ��������� ������ ����������)

                                    // �������� ����� ��� ��������� ���������:
        glEnable(GL_LIGHTING);

        // ������ ������� ����� � 0 (�� ���� ���� �� 8), ����� ���� ������ � "����":
        glEnable(GL_LIGHT0);


        // ������� �� ������:
        for (int i = 0; i < shapes.size(); i++)
        {
            shapes[i]->draw();
        }
        for (int i = 0; i < numbers.size(); i++)
        {
            numbers[i]->draw();
        }

        // �������� ���, �� ��������:
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glFlush();
        // �������� ����:
        glutSwapBuffers(); // ����������� ������
    }

    // ���������� ��䳿, ���'����� � ����� ������ ���� 
    void Scene::on_size(int width, int height)
    {
        this->width = width;
        if (height == 0)
            height = 1;
        this->height = height;
    }

    // ���������� ����, ���'������ � ����������� ������ ����
    void Scene::on_mouse(int button, int state, int x, int y)
    {
        // �������� ������ ���������� ����:
        mouseX = x;
        mouseY = y;
        if ((state == GLUT_UP)) // ������ ������
        {

            // �������� ��������� ���:
            if (fields[M - 1][0] == 1 && fields[M - 1][1] == 2 && fields[M - 1][2] == 3)
            {
                finish = true;
            }
            this->button = -1;  
            return;
        }
        this->button = button;  // �������� ���������� ��� ������
        if (finish)
        {
            return;
        }
        
        if (button == 0 && findNearest(x, y, xFrom, zFrom))
        {
            Logic(xFrom, zFrom);
        }
        if (button == 2 && findNearest(x, y, xFrom, zFrom))
        {
            Flag(xFrom, zFrom);
        }
    }

    // ���������� ����, ���'������ � ������������ ���� � ���������� �������
    void Scene::on_motion(int x, int y)
    {
        switch (button)
        {
        case 2: // ����� ������ - ��������� �����
            angleX += x - mouseX;
            angleY += y - mouseY;
            mouseX = x;
            mouseY = y;
            break;
        }
    }

    // ���������� ����, ���'������ � ����������� �������������� ����� � ������ 
    void Scene::on_special(int key, int x, int y)
    {
        switch (key) {
        case GLUT_KEY_UP:   // ����������
            if (distZ > -1.7)
            {
                break;
            }
            distZ += 0.1;
            break;
        case GLUT_KEY_DOWN: // ���������
            distZ -= 0.1;
            break;
        case GLUT_KEY_F2:   // ���� ���
            initialize();
            break;
        }
    }

    int tick = 0; // ��������, �������� ����� ��������� ���� 25 ��

    void Scene::on_timer(int value)
    {
        tick++;
        if (tick >= 40) // ���������� �������� �������
        {
            if (!finish)// ������� �����������, ���� ��� �� ��������
            {
                timel++;
            }
            tick = 0;   // ������� ��������
        }
        on_paint();     // ��������� ������������� ����
    }

}
