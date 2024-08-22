//��̬����ʵ��˳���
/*
#include<stdio.h>
#include<stdlib.h>
#define max 100

typedef struct {
    int data[max];
    int last;
} sqlist;

void initlist(sqlist* l) {  // Pass by reference to initialize
    l->last = 0;
    printf("��ʼ������ɣ��ñ���Ϊ�ձ�\n");
}

void createlist(sqlist* l, int n) {  // Create list
    int i = 0;
    int j;
    for (i = 0; i < n; i++) {
        scanf_s("%d", &j);
        l->data[i] = j;
    }
    l->last = n;
}

void insertelem(sqlist* l, int i, int e) {
    int k;
    if (i < 0 || i > l->last) {
        printf("�����λ�ò��Ϸ�\n");
        return;
    }
    if (l->last >= max) {  // Use '>=' to avoid overflow
        printf("�������޷�����\n");
        return;
    }
    for (k = l->last; k >= i; --k) {  // Fix the loop by removing the semicolon
        l->data[k + 1] = l->data[k];
    }
    l->data[i] = e;  // Insert the new element at position i
    l->last++;
}

int deletelem1(sqlist* l, int i) {
    int k;
    if (i < 0 || i >= l->last) {  // Use '>=' to avoid invalid index
        printf("ɾ����λ�ò��Ϸ�\n");
        return 0;
    }
    printf("ɾ����Ԫ��Ϊ%d\n", l->data[i]);
    for (k = i; k < l->last - 1; ++k) {  // Adjust loop to shift elements correctly
        l->data[k] = l->data[k + 1];
    }
    l->last--;
    return 1;
}

int findelem(sqlist* l, int e) {
    int k;
    for (k = 0; k < l->last; k++) {
        if (l->data[k] == e) {
            printf("���ҳɹ�����Ԫ����˳����е�λ��Ϊ%d\n", k);
            return 1;
        }
    }
    printf("����ʧ��\n");
    return 0;
}

int getelem(sqlist* l, int i) {
    if (i < 0 || i >= l->last) {  // Use '>=' to avoid invalid index
        printf("����λ�ò��Ϸ�\n");
        return 0;
    }
    printf("��%d��Ԫ��Ϊ%d\n", i, l->data[i]);
    return 1;
}

void printlist(sqlist l) {
    int i = 0;
    while (i < l.last) {
        printf("%d\t", l.data[i]);
        ++i;
    }
    printf("\n");
}

int main() {
    sqlist l;
    initlist(&l);  // Pass the address of l
    int n;
    printf("����������Ԫ�صĸ�����\n");
    scanf_s("%d", &n);
    printf("����˳���������Ԫ�أ�\n");
    createlist(&l, n);
    printlist(l);

    int i;
    printf("������Ҫɾ����Ԫ�ص�λ��:\n");
    scanf_s("%d", &i);
    deletelem1(&l, i);
    printlist(l);

    printf("��������Ҫ���ҵ�Ԫ��ֵ��\n");
    int a;
    scanf_s("%d", &a);
    findelem(&l, a);

    printf("��������Ҫ���ҵ�Ԫ�ص�λ�ã�\n");
    int p;
    scanf_s("%d", &p);
    getelem(&l, p);

    return 0;
}
*/
//��̬����ʵ��˳���
#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int* data;  // ��̬����
    int last;   // ��ʾ������Ԫ�صĸ���
    int capacity;  // ���������
} sqlist;

// ��ʼ��
void initlist(sqlist* l, int initial_capacity) {
    l->data = (int*)malloc(initial_capacity * sizeof(int));
    if (l->data == NULL) {
        printf("�ڴ����ʧ��\n");
        exit(1);
    }
    l->last = 0;
    l->capacity = initial_capacity;
    printf("��ʼ������ɣ��ñ���Ϊ�ձ�\n");
}

// ��̬���������С
void resize(sqlist* l, int new_capacity) {
    int* new_data = (int*)realloc(l->data, new_capacity * sizeof(int));
    if (new_data == NULL) {
        printf("�ڴ����·���ʧ��\n");
        exit(1);
    }
    l->data = new_data;
    l->capacity = new_capacity;
}

// ������
void createlist(sqlist* l, int n) {
    if (n > l->capacity) {
        resize(l, n);
    }
    for (int i = 0; i < n; i++) {
        scanf_s("%d", &l->data[i]);
    }
    l->last = n;
}

// ����Ԫ��
void insertelem(sqlist* l, int i, int e) {
    if (i < 0 || i > l->last) {
        printf("�����λ�ò��Ϸ�\n");
        return;
    }
    if (l->last >= l->capacity) {
        resize(l, l->capacity * 2);  // ��̬���������С
    }
    for (int k = l->last; k > i; --k) {
        l->data[k] = l->data[k - 1];
    }
    l->data[i] = e;
    l->last++;
}

// ɾ��Ԫ��
int deletelem1(sqlist* l, int i) {
    if (i < 0 || i >= l->last) {
        printf("ɾ����λ�ò��Ϸ�\n");
        return 0;
    }
    printf("ɾ����Ԫ��Ϊ%d\n", l->data[i]);
    for (int k = i; k < l->last - 1; ++k) {
        l->data[k] = l->data[k + 1];
    }
    l->last--;
    return 1;
}

// ����Ԫ��ֵ
int findelem(sqlist* l, int e) {
    for (int k = 0; k < l->last; k++) {
        if (l->data[k] == e) {
            printf("���ҳɹ�����Ԫ����˳����е�λ��Ϊ%d\n", k);
            return 1;
        }
    }
    printf("����ʧ��\n");
    return 0;
}

// ��λ�ò���Ԫ��
int getelem(sqlist* l, int i) {
    if (i < 0 || i >= l->last) {
        printf("����λ�ò��Ϸ�\n");
        return 0;
    }
    printf("��%d��Ԫ��Ϊ%d\n", i, l->data[i]);
    return 1;
}

// ��ӡ�б�
void printlist(sqlist* l) {
    for (int i = 0; i < l->last; i++) {
        printf("%d\t", l->data[i]);
    }
    printf("\n");
}

// �ͷ��ڴ�
void freelist(sqlist* l) {
    free(l->data);
    l->data = NULL;
    l->capacity = 0;
    l->last = 0;
}

int main() {
    sqlist l;
    initlist(&l, 10);  // ��ʼ����̬���飬��ʼ����Ϊ10

    int n;
    printf("����������Ԫ�صĸ�����\n");
    scanf_s("%d", &n);
    printf("����˳���������Ԫ�أ�\n");
    createlist(&l, n);
    printlist(&l);

    int i;
    printf("������Ҫɾ����Ԫ�ص�λ��:\n");
    scanf_s("%d", &i);
    deletelem1(&l, i);
    printlist(&l);

    printf("��������Ҫ���ҵ�Ԫ��ֵ��\n");
    int a;
    scanf_s("%d", &a);
    findelem(&l, a);

    printf("��������Ҫ���ҵ�Ԫ�ص�λ�ã�\n");
    int p;
    scanf_s("%d", &p);
    getelem(&l, p);

    freelist(&l);  // �ͷŶ�̬������ڴ�

    return 0;
}
