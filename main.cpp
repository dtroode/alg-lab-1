#include <iostream>
using namespace std;


// Структутра класса очереди
class Queue {
private:
    struct queue {
        int value;
        queue* next;
    };
    queue* head;

public:
    Queue();                   // Конструктор
    ~Queue();                  // Деструктор
    bool Empty();              // Проверка на пустоту
    void Push(int value);      // Добавление элемента в конец
    int Pop();                 // Вытаскивание элемента из начала
    int Pop(int pos);          // Вытаскивание элемента по позиции
    int Get();                 // Получение элемента из начала
    int Get(int pos);          // Получение элемента по позиции
    void Set(int value);                 // Установка элемента из начала
    void Set(int value, int pos);          // Установка элемента по позиции
    int Size();                // Размер очереди
    void ShowAll();            // Вывод всех элементов очереди
};

// Определение конструктора, деструктора и методов класса очереди
Queue::Queue() {
    head = nullptr;
}

Queue::~Queue() {
    while (head != nullptr)
        head = head->next;
    delete head;
}

bool Queue::Empty() {
    return head == nullptr;
}

void Queue::Push(int value) {
    auto* temp = new(queue);
    temp->value = value;
    temp->next = nullptr;

    if (head == nullptr) head = temp;
    else {
        queue* last = head;
        while (last->next != nullptr)
            last = last->next;
        last->next = temp;
    }
}

int Queue::Pop() {
    if (Empty()) return -1;

    int value = head->value;
    head = head->next;
    return value;
}

int Queue::Pop(int pos) {
    if (Empty()) return -1;

    for (int i = 0; i < pos; i++) Push(Pop());
    int value = Pop();
    return value;
}

int Queue::Get() {
    return head->value;
}

int Queue::Get(int pos) {
    for (int i = 0; i < pos; i++) Push(Pop());

    int value = Get();

    for (int i = pos; i < Size(); i++) Push(Pop());

    return value;
}

void Queue::Set(int value) {
    head->value = value;
}

void Queue::Set(int value, int pos) {
    for (int i = 0; i < pos; i++) Push(Pop());

    head->value = value;

    for (int i = pos; i < Size(); i++) Push(Pop());
}

int Queue::Size() {
    if (Empty()) return 0;

    queue* last = head;
    int size = 1;
    while (last->next != nullptr)
    {
        last = last->next;
        size++;
    }

    return size;
}

void Queue::ShowAll() {
    for (int i = 0; i < Size(); i++) {
        std::cout << Get(i) << std::endl;
    }
}




// Метод для поиска медианного элемента
// Выбирается медианный среди первого, последнего и среднего элементов
int findMedian(Queue *queue) {
    int size = queue->Size();
    int mid = size / 2;

    if (queue->Get(mid) < queue->Get()) {
        int temp = queue->Get();
        queue->Set(queue->Get(size / 2));
        queue->Set(temp, size / 2);
    }
    if (queue->Get(size - 1) < queue->Get()) {
        int temp = queue->Get();
        queue->Set(queue->Get(size - 1));
        queue->Set(temp, size - 1);
    }
    if (queue->Get(mid) < queue->Get(size - 1)) {
        int temp = queue->Get(size - 1);
        queue->Set(queue->Get(size / 2), size - 1);
        queue->Set(temp, size / 2);
    }
    return queue->Get(size - 1);
}

// Метод сортировки по Хоару
Queue Sort(Queue *queue) {
    int size = queue->Size();

    if (size <= 1) return *queue;
    else {
        // Медианный элемент для сравнения
        int pivot = findMedian(queue);

        // Инициализируем очереди для:
        // 1. элементов меньше медианного,
        // 2. элементов равных медианному,
        // 3. элементов больше медианного,
        // и очередь для вывода
        auto *low   = new(Queue);
        auto *equal = new(Queue);
        auto *high  = new(Queue);
        auto *res   = new(Queue);

        // Заполняем три очереди
        for (int i = 0; i < size; i++) {
            int elem = queue->Get(i);
            if (elem < pivot) low->Push(elem);
            else if (elem > pivot) high->Push(elem);
            else equal->Push(elem);
        }

        // Сортируем очереди
        *low = Sort(low);
        *high = Sort(high);

        // Складываем очереди в результирующую
        for (int i = 0; i < low->Size();   i++) res->Push(low->Get(i));
        for (int i = 0; i < equal->Size(); i++) res->Push(equal->Get(i));
        for (int i = 0; i < high->Size();  i++) res->Push(high->Get(i));

        return *res;
    }
}




int main() {
    auto *q = new(Queue);
    q->Push(5);
    q->Push(5);
    q->Push(-1);
    q->Push(6);
    q->Push(2);
    q->Push(8);
    q->Push(1);
    q->Push(15);
    q->Push(100);
    q->Push(5);
    q->Push(2);
    q->Push(-5);
    q->Push(5);
    q->Push(81);
    Queue res = Sort(q);
    res.ShowAll();
    return 0;
}
