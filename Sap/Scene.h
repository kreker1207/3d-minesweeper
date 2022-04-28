#ifndef Scene_h
#define Scene_h

#include "Shape.h"

#include <vector>

namespace Sapper
{

    const int M = 10, N = 10; 

                           
    class Scene
    {
        std::vector<Shape*> shapes; // "�������" ����� ��������� �� �������� ���
        std::vector<Shape*> numbers;
        Shape* boards[10][10];
        int counter;
        int button;           // ������ ���� (-1 - �� ���������, 0 - ���, 2 - �����)
        float angleX, angleY; // �������� ��� �������� ����� 
        float mouseX, mouseY; // ������ ����������
        float width, height;  // ������ ����
        float distZ;          // ������� �� �� Z �� �����
        bool finish;          // ������ ����, �� ��� ���������
        
        float xStep, zStep;   // ������� �� �������� ���������
        int timel;             // �������� ��� � ��������
        int fields[M][N];     // �����, � ����� ������������ ��������� �����:

        int xFrom, zFrom;     // ������� �������, � ����� ���������� �����������
        int xTo, zTo;         // ������� �������, ���� ���������� �����������
        double x, y, z;
        int m = 10, n = 10, mines = 0, flags = 0, rgh = 0, res;
    public:
        Scene(float xStep, float zStep);
        ~Scene();
        void clearNum(int i,int j);
        void on_paint();
        void on_size(int width, int height);
        void on_mouse(int button, int state, int x, int y);
        void on_motion(int x, int y);
        void on_special(int key, int x, int y);
        void on_timer(int value);
    private:
        void Flag(int j, int i);
        void check();
        void initialize();
        void Logic(int x, int z);
        bool findNearest(int x, int z, int& x1, int& z1);
        void resetArr();
        float allocX(int i);
        float allocZ(int i);
    };

}

#endif

