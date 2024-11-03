#include "../utils/common.hpp"

 /* �б��� */
class MyList {
private:
    int* arr;             // ���飨�洢�б�Ԫ�أ�
    int arrCapacity = 10; // �б�����
    int arrSize = 0;      // �б��ȣ���ǰԪ��������
    int extendRatio = 2;   // ÿ���б����ݵı���

public:
    /* ���췽�� */
    MyList() {
        arr = new int[arrCapacity];
    }

    /* �������� */
    ~MyList() {
        delete[] arr;
    }

    /* ��ȡ�б��ȣ���ǰԪ��������*/
    int size() {
        return arrSize;
    }

    /* ��ȡ�б����� */
    int capacity() {
        return arrCapacity;
    }

    /* ����Ԫ�� */
    int get(int index) {
        // �������Խ�磬���׳��쳣����ͬ
        if (index < 0 || index >= size())
            throw out_of_range("����Խ��");
        return arr[index];
    }

    /* ����Ԫ�� */
    void set(int index, int num) {
        if (index < 0 || index >= size())
            throw out_of_range("����Խ��");
        arr[index] = num;
    }

    /* ��β�����Ԫ�� */
    void add(int num) {
        // Ԫ��������������ʱ���������ݻ���
        if (size() == capacity())
            extendCapacity();
        arr[size()] = num;
        // ����Ԫ������
        arrSize++;
    }

    /* ���м����Ԫ�� */
    void insert(int index, int num) {
        if (index < 0 || index >= size())
            throw out_of_range("����Խ��");
        // Ԫ��������������ʱ���������ݻ���
        if (size() == capacity())
            extendCapacity();
        // ������ index �Լ�֮���Ԫ�ض�����ƶ�һλ
        for (int j = size() - 1; j >= index; j--) {
            arr[j + 1] = arr[j];
        }
        arr[index] = num;
        // ����Ԫ������
        arrSize++;
    }

    /* ɾ��Ԫ�� */
    int remove(int index) {
        if (index < 0 || index >= size())
            throw out_of_range("����Խ��");
        int num = arr[index];
        // ������ index ֮���Ԫ�ض���ǰ�ƶ�һλ
        for (int j = index; j < size() - 1; j++) {
            arr[j] = arr[j + 1];
        }
        // ����Ԫ������
        arrSize--;
        // ���ر�ɾ����Ԫ��
        return num;
    }

    /* �б����� */
    void extendCapacity() {
        // �½�һ������Ϊԭ���� extendRatio ����������
        int newCapacity = capacity() * extendRatio;
        int* tmp = arr;
        arr = new int[newCapacity];
        // ��ԭ�����е�����Ԫ�ظ��Ƶ�������
        for (int i = 0; i < size(); i++) {
            arr[i] = tmp[i];
        }
        // �ͷ��ڴ�
        delete[] tmp;
        arrCapacity = newCapacity;
    }

    /* ���б�ת��Ϊ Vector ���ڴ�ӡ */
    vector<int> toVector() {
        // ��ת����Ч���ȷ�Χ�ڵ��б�Ԫ��
        vector<int> vec(size());
        for (int i = 0; i < size(); i++) {
            vec[i] = arr[i];
        }
        return vec;
    }
};

/* Driver Code */
int main() {
    /* ��ʼ���б� */
    MyList* nums = new MyList();
    /* ��β�����Ԫ�� */
    nums->add(1);
    nums->add(3);
    nums->add(2);
    nums->add(5);
    nums->add(4);
    cout << "�б� nums = ";
    vector<int> vec = nums->toVector();
    printVector(vec);
    cout << "���� = " << nums->capacity() << " ������ = " << nums->size() << endl;

    /* ���м����Ԫ�� */
    nums->insert(3, 6);
    cout << "������ 3 ���������� 6 ���õ� nums = ";
    vec = nums->toVector();
    printVector(vec);

    /* ɾ��Ԫ�� */
    nums->remove(3);
    cout << "ɾ������ 3 ����Ԫ�أ��õ� nums = ";
    vec = nums->toVector();
    printVector(vec);

    /* ����Ԫ�� */
    int num = nums->get(1);
    cout << "�������� 1 ����Ԫ�أ��õ� num = " << num << endl;

    /* ����Ԫ�� */
    nums->set(1, 0);
    cout << "������ 1 ����Ԫ�ظ���Ϊ 0 ���õ� nums = ";
    vec = nums->toVector();
    printVector(vec);

    /* �������ݻ��� */
    for (int i = 0; i < 10; i++) {
        // �� i = 5 ʱ���б��Ƚ������б���������ʱ�������ݻ���
        nums->add(i);
    }
    cout << "���ݺ���б� nums = ";
    vec = nums->toVector();
    printVector(vec);
    cout << "���� = " << nums->capacity() << " ������ = " << nums->size() << endl;

    // �ͷ��ڴ�
    delete nums;

    return 0;
}
