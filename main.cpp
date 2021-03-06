#include <iostream>
using namespace std;

// Структутра класса очереди
class Queue
{
private:
    /*
     * Структура элемента очереди:
     * значение и ссылка-указатель на следующий элемент.
     */
    struct queue
    {
        int value;
        queue *next;
    };
    // Голова и хвост: будут указателями на первый и последний элементы
    queue *head;
    queue *tail;

public:
    Queue();                      // Конструктор
    ~Queue();                     // Деструктор
    bool IsEmpty();               // Проверка на пустоту
    void Push(int value);         // Добавление элемента в конец
    int Pop();                    // Вытаскивание элемента из начала
    int Pop(int pos);             // Вытаскивание элемента по позиции
    int Get();                    // Получение элемента из начала
    int Get(int pos);             // Получение элемента по позиции
    void Set(int value);          // Установка элемента из начала
    void Set(int value, int pos); // Установка элемента по позиции
    int Size();                   // Размер очереди
    void ShowAll();               // Вывод всех элементов очереди
};

/*
 * Конструктор
 * Устаналиваем указатель головы на NULL.
*/
Queue::Queue()
{
    head = nullptr;
    tail = nullptr;
}

/*
 * Деструктор
 * Сдвигаем голову к последнему элементу, предыдущие постепенно удаляются,
 * так как ссылки на них больше нет.
 * Удаляем последний элемент вручную.
*/
Queue::~Queue()
{
    while (head != nullptr)
        head = head->next;
    delete head;
}

/*
 * Проверка на пустоту
 * Если голова указывает на NULL, то очередь пуста.
*/
bool Queue::IsEmpty()
{
    return head == nullptr;
}

/*
 * Добавление элемента в конец
 * 1. Создаём элемент со значением и ссылкой на NULL.
 * 2. Если голова указывает на NULL, то ставим указатель на новый элемент.
 * 3. Если есть первый элемент, то идём до последнего элемента
 *    и ставим указатель next на новый элемент.
 */
void Queue::Push(int value)
{
    auto *temp = new (queue);
    temp->value = value;
    temp->next = nullptr;

    if (head == nullptr) {
        head = temp;
        tail = head;
    }
    else
    {
        tail->next = temp;
        tail = tail->next;
    }
}

/*
 * Вытаскиваем первый элемент
 * Получаем его значение и сдвигаем указатель головы.
 */
int Queue::Pop()
{
    if (IsEmpty())
        return -1;

    int value = head->value;
    head = head->next;
    return value;
}

/*
 * Перегрузка метода получения элемента
 * Вытаскиваем элемент по его позиции, для этого:
 * 1. Прокручиваем очередь (вытаскиваем первый элемент и вставляем в конец) так,
 *    что нужный элемент становится первым.
 * 2. Вытаскиваем нужный элемент.
 * 3. Прокручиваем очередь на оставшееся количество символов, чтоб вернуть в прежнее состояние.
 */
int Queue::Pop(int pos)
{
    if (IsEmpty())
        return -1;

    for (int i = 0; i < pos; i++)
        Push(Pop());

    int value = Pop();

    for (int i = pos; i < Size(); i++)
        Push(Pop());
    return value;
}

/*
 * Получаем значение первого элемента
 */
int Queue::Get()
{
    if (IsEmpty())
        return -1;

    return head->value;
}

/*
 * Перегрузка метода получения значения элемента
 * Получаем значение элемента по позиции, для этого:
 * 1. Прокручиваем очередь (вытаскиваем первый элемент и вставляем в конец) так,
 *    что нужный элемент становится первым.
 * 2. Получаем значение нужного элемента.
 * 3. Прокручиваем очередь на оставшееся количество символов, чтоб вернуть в прежнее состояние.
 */
int Queue::Get(int pos)
{
    if (IsEmpty())
        return -1;

    for (int i = 0; i < pos; i++)
        Push(Pop());

    int value = Get();

    for (int i = pos; i < Size(); i++)
        Push(Pop());

    return value;
}

/*
 * Устанавливаем значение элемента
 */
void Queue::Set(int value)
{
    head->value = value;
}

/*
 * Перегрузка метода установки значения элемента
 * Устанавливаем значение элемента по позиции, для этого:
 * 1. Прокручиваем очередь (вытаскиваем первый элемент и вставляем в конец) так,
 *    что нужный элемент становится первым.
 * 2. Устанавливаем значение нужного элемента.
 * 3. Прокручиваем очередь на оставшееся количество символов, чтоб вернуть в прежнее состояние.
 */
void Queue::Set(int value, int pos)
{
    for (int i = 0; i < pos; i++)
        Push(Pop());

    Set(value);

    for (int i = pos; i < Size(); i++)
        Push(Pop());
}

/*
 * Получаем размер очереди
 * Создаём новый указатель, который равен указателю головы,
 * сдвигаем его, пока не дойдём до последнего элемента и считаем эти шаги.
 */
int Queue::Size()
{
    if (IsEmpty())
        return 0;

    queue *current = head;
    int size = 1;
    while (current->next != nullptr)
    {
        current = current->next;
        size++;
    }

    return size;
}

/*
 * Вывод всех элементов
 * Временный указатель указывает на голову,
 * выводит её и смещается, выводя все элементы.
 */
void Queue::ShowAll()
{
    if (IsEmpty())
        cout << "Очередь пуста" << endl;

    queue *temp = head;
    while(temp) {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}




/*
 * Метод для поиска медианного элемента
 * Выбирается медианный среди первого, последнего и среднего элементов.
 */
int findMedian(Queue *queue)
{
    int size = queue->Size();
    int mid = size / 2;

    int first = queue->Get();
    int middle = queue->Get(mid);
    int last = queue->Get(size - 1);

    if (middle < first);
    {
        int temp = first;
        queue->Set(middle);
        queue->Set(temp, mid);
    }
    if (last < first);
    {
        int temp = first;
        queue->Set(last);
        queue->Set(temp, size - 1);
    }
    if (middle < last);
    {
        int temp = last;
        queue->Set(middle, size - 1);
        queue->Set(temp, mid);
    }
    return queue->Get(size - 1);
}




// Метод сортировки по Хоару
Queue Sort(Queue *queue)
{
    int size = queue->Size();

    if (size <= 1)
        return *queue;
    else
    {
        // Медианный элемент для сравнения
        int pivot = findMedian(queue);

        /*
         * Инициализируем очереди для:
         * 1. элементов меньше медианного;
         * 2. элементов равных медианному;
         * 3. элементов больше медианного;
         * и очередь для вывода.
         */
        auto *low = new (Queue);
        auto *equal = new (Queue);
        auto *high = new (Queue);
        auto *res = new (Queue);

        // Заполняем три очереди
        for (int i = 0; i < size; i++)
        {
            int elem = queue->Get(i);
            if (elem < pivot)
                low->Push(elem);
            else if (elem > pivot)
                high->Push(elem);
            else
                equal->Push(elem);
        }



        // Сортируем очереди
        *low = Sort(low);
        *high = Sort(high);

        // Складываем очереди в результирующую
        for (int i = 0; i < low->Size(); i++)
            res->Push(low->Get(i));
        for (int i = 0; i < equal->Size(); i++)
            res->Push(equal->Get(i));
        for (int i = 0; i < high->Size(); i++)
            res->Push(high->Get(i));

        return *res;
    }
}




int main()
{
    return 0;
}
