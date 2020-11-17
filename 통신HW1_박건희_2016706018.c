//2016706018 �ڰ���
//header
#include <stdio.h>

//matched filter function
void rect_filter(char file_name[20], int opt, int sample_nun, int bit_num);		//input 1 2 3�� matched filter�� ���б��Լ�
void tri_filter(char file_name[20], int opt, int bit_num);							//input 4�� matched filter �Լ�


//main function
int main() {
	rect_filter("input#1.dat", 0, 10, 1000);	//input#1.dat ���ذ�0, ��Ʈ�� ���ü� 10, ��Ʈ �� 1000
	rect_filter("input#2.dat", 100, 10, 1000);	//input#2.dat ���ذ�100, ��Ʈ�� ���ü� 10, ��Ʈ �� 1000
	rect_filter("input#3.dat", 0, 20, 500);		//input#3.dat ���ذ�0, ��Ʈ�� ���ü� 20, ��Ʈ �� 500
	rect_filter("input#4.dat", 0, 10, 1000);	//input#4.dat ���ذ�0, ��Ʈ�� ���ü� 10, ��Ʈ �� 1000
	tri_filter("input#4.dat", 0, 1000);			//input#4.dat ���ذ�0, ��Ʈ �� 1000 (������ ����)
}



/*
���б� �Լ�
precondition���� �����̸�, ���н� ������, ��Ʈ�� sample ����, ��Ʈ ���� ���ڷ� �޴´�.
*/
void rect_filter(char file_name[20],int opt, int sample_num, int bit_num) {
	FILE* fin, *fbit;						//���ϱ���ü�� ������ ����
	fopen_s(&fin, file_name, "rt");			//fin�� file_name ���ڿ� ���� ���� txt ���·� �б�
	fopen_s(&fbit, "bit.dat", "rt");		//fbit�� bit.dat ���� txt ���·� �б�
	float input[20] = { 0.0, };				// ���� �迭, sample ���� 10�� �Ǵ� 20���� ���� ����ؼ� 20���� ����
	float sum = 0;							// ���а�
	int detect;								// ���а��� ����ġ���� ũ�� �۳ķ� ������ bit
	int bit;								// bit.dat�� ����� ���� bit
	int i, k;								// �ݺ����� 
	float error_count = 0;					// ���� bit ����

	for (i = 0; i < bit_num; i++) {			//bit���� ��ŭ �ݺ�
		for (k = 0; k < sample_num; k++) {	//bit�� sample����ŭ �ݺ�
			fscanf_s(fin, "%f", &input[k]);	//bit�� sample�� input�迭�� ������� ����
			sum += input[k];				//sample�� ����
		}									//for�� ����� sum�� bit �ϳ��� sample ���а� ����
		if (sum > opt)						//���а��� ���غ��� ũ�� 1, ������ 0
			detect = 1;
		else if (sum < opt)
			detect = 0;
		fscanf_s(fbit, "%d", &bit);			//���� bit �о����
		if (detect != bit)					//���� ������ bit�� ���� bit�� �ٸ��� 
			error_count++;					//���� ���� �߰�

		sum = 0;							//���а� 0 �ʱ�ȭ
	}
	//��� bit�� ���� ����

	printf("%s rect_filter error_count: %d, error_rate: %.1f%%\n", file_name, (int)error_count, error_count/ (float)bit_num *100);		//���� �̸�, ������Ʈ����, ��Ʈ������ ���
}


/*
input#4�� 
������ ����
*/
void tri_filter(char file_name[20], int opt, int bit_num) {	//�����̸�,���ذ�,��Ʈ�� ����
	FILE* fin;
	FILE* fbit;
	fopen_s(&fbit, "bit.dat", "rt");
	fopen_s(&fin, file_name, "rt");			//rect matched filter�� ���������� ���� �д� ����
	float input[10] = { 0.0, };				//���� ����
	float filter[10] = { 0,6,10,12,15,15,12,10,6,0 };		//������ ���� ������ ���� ���� bit������ ����� ���� ����
	float sum = 0;	//��갪
	int detect;		//��갪�� ���ذ� ���� ũ�� 1 ������ 0
	int bit;		//���� bit
	int i, k;		//for����
	float error_count = 0;	//���� ��Ʈ ����

	for (i = 0; i < bit_num; i++) {			//bit����ŭ �ݺ�
		for (k = 0; k < 10; k++) {			//bit������ ���͸� ���� �� ����
			fscanf_s(fin, "%f", &input[k]);
			sum += filter[k]*input[k];
		}
		if (sum > opt)		//��갪�� ���غ��� ũ�� 1 ������ 0
			detect = 1;
		else if(sum < opt) 
			detect = 0;
		fscanf_s(fbit, "%d", &bit);	//���� bit�� ���� ������ 0 ũ�� 1
		if (detect != bit)
			error_count++;
		sum = 0;	//��갪 0 �ʱ�ȭ
	}
	printf("%s tri_filter error_count: %d, error_rate: %.1f%%\n", file_name,(int)error_count, (error_count / (float)bit_num * 100));	//���� �̸�, ������Ʈ����, ��Ʈ������ ���
}




