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
    // Голова: будет указателем на первый элемент
    queue *head;

public:
    Queue();                      // Конструктор
    ~Queue();                     // Деструктор
    bool isEmpty();               // Проверка на пустоту
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
bool Queue::isEmpty()
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

    if (head == nullptr)
        head = temp;
    else
    {
        queue *last = head;
        while (last->next != nullptr)
            last = last->next;
        last->next = temp;
    }
}

/*
 * Вытаскиваем первый элемент
 * Получаем его значение и сдвигаем указатель головы.
*/
int Queue::Pop()
{
    if (isEmpty())
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
    if (isEmpty())
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
    if (isEmpty())
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
    if (isEmpty())
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

    head->value = value;

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
    if (isEmpty())
        return 0;

    queue *last = head;
    int size = 1;
    while (last->next != nullptr)
    {
        last = last->next;
        size++;
    }

    return size;
}

/*
 * Вывод всех элементов
 */
void Queue::ShowAll()
{
    for (int i = 0; i < Size(); i++)
    {
        std::cout << Get(i) << std::endl;
    }
}




/*
 * Метод для поиска медианного элемента
 * Выбирается медианный среди первого, последнего и среднего элементов.
 */
int findMedian(Queue *queue)
{
    int size = queue->Size();
    int mid = size / 2;

    if (queue->Get(mid) < queue->Get())
    {
        int temp = queue->Get();
        queue->Set(queue->Get(size / 2));
        queue->Set(temp, size / 2);
    }
    if (queue->Get(size - 1) < queue->Get())
    {
        int temp = queue->Get();
        queue->Set(queue->Get(size - 1));
        queue->Set(temp, size - 1);
    }
    if (queue->Get(mid) < queue->Get(size - 1))
    {
        int temp = queue->Get(size - 1);
        queue->Set(queue->Get(size / 2), size - 1);
        queue->Set(temp, size / 2);
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
    auto *q = new (Queue);
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
    std::cout << q->Get() << std::endl;
    q->Get(5);
    std::cout << q->Get() << std::endl;
//    Queue res = Sort(q);
//    res.ShowAll();
    return 0;
}
