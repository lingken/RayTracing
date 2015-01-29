#include "Scene.h"
#include "stdafx.h"
#include <cstdio>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;

int main(int argc, char **argv)
{
	cv::Mat img; //������һ������������ڴ洢ͼ������
	img.create(SCREEN_HEIGHT, SCREEN_WIDTH, CV_8UC3);//600��,800�У�(800 * 600)ÿ��Ԫ����ռ�ռ�Ϊ����unsigned char��
	img.setTo(cv::Scalar(255,255,255));//��ȫͼ����Ϊbgr��ɫ��255��255��255����ɫ

	Scene scene;
	scene.init_scene();

	Vertex v_pos = Vertex(0, 0, -1000); Vector v_dir = Vector(0, 0, 1);
	
	if (argc > 1){
		v_pos.x = atof(argv[2]);
		v_pos.y = atof(argv[3]);
		v_pos.z = atof(argv[4]);
		v_dir.x = atof(argv[5]);
		v_dir.y = atof(argv[6]);
		v_dir.z = atof(argv[7]);
	}

	scene.change_view_position(v_pos);
	scene.change_view_direction(v_dir);
	
	scene.render();

	
	for (int x = 0; x < img.rows; x ++){
		for (int y = 0; y < img.cols; y ++){
			int pos = x * SCREEN_WIDTH * 3 + y * 3;
			double r = scene.camera.pixels[pos];
			double g = scene.camera.pixels[pos+1];
			double b = scene.camera.pixels[pos+2];
			int v_x = SCREEN_HEIGHT - x - 1;
			r = min(r * 255, 255);
			g = min(g * 255, 255);
			b = min(b * 255, 255);
			img.ptr<uchar>(v_x)[y*3] = b;
			img.ptr<uchar>(v_x)[y*3 + 1] = g;
			img.ptr<uchar>(v_x)[y*3 + 2] = r;
		}
	}
	

	//system("pause");
	//�ҵ�pixels��x���������ϣ���img��x����������
	
	cv::imshow("####Lincoln", img); //��ʾͼ��img��һ������show�Ĵ�����
	if (argc > 1)
		cv::imwrite(argv[1], img);
	cv::waitKey(0); //�ȴ�������Ϣ���˳�
	//system("pause");
	return 0;
}

