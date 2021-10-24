using System;
using System.Collections.Generic;

namespace Hoar
{
  public class Queue
  {
    // Конструктор и список. Очередь работает на основе динамического массива 
    private List<int> arr;
    public Queue()
    {
      this.arr = new List<int>();
    }

    
    // Проверка очереди на пустоту
    public bool empty()
    {
      if (arr.Count == 0)
        return true;
      else return false;
    }

    
    // Добавление элемента в конец
    public void push(int element)
    {
      arr.Add(element);
    }

    
    // Достаём элемент и удаляем его. Два перегруженных метода.
    // По умолчанию достаётся элемент из начала, можно указать позицию
    public int pop()
    {
      try
      {
        int element = arr[0];
        arr.RemoveAt(0);
        return element;
      }
      catch (Exception e)
      {
        throw e;
      }
    }
    
    public int pop(int pos)
    {
      try
      {
        for (int i = 0; i < pos; i++)
          push(pop());
        
        int element = get();
        arr.RemoveAt(0);
        return element;
      }
      catch (Exception e)
      {
        throw e;
      }
    }

    
    // Возвращаем элемент. Два перегруженных метода.
    // По умолчанию возвращается элемент из начала, можно указать позицию
    public int get()
    {
      return arr[0];
    }

    public int get(int pos)
    {
      for (int i = 0; i < pos; i++)
        push(pop());

      int result = get();
      
      for (int i = pos; i < size(); i++)
        push(pop());

      return result;
    }

    
    // Устанаваливаем элемент. Два перегруженных метода.
    // По умолчанию устанаваливается элемент из начала, можно указать позицию
    public void set(int element)
    {
      arr[0] = element;
    }
    
    public void set(int element, int pos)
    {
      for (int i = 0; i < pos; i++)
        push(pop());
      
      arr[0] = element;
      
      for (int i = pos; i < size(); i++)
        push(pop());
    }

    
    // Размер очереди
    public int size()
    {
      return arr.Count;
    }
  }
  
  
  internal class Program
  {
    public static void Main(string[] args)
    {
    }

    
    // Метод сортировки
    public Queue sort(Queue arr)
    {
      int size = arr.size();

      // Если размер больше единицы, сортируем, если нет – возвращаем очередь обратно
      if (size > 1)
      {
        // Медианный элемент для сравнения
        int middle = arr.get(size / 2);
        
        // Инициализируем очереди для:
        // 1. элементов меньше медианного,
        // 2. элементов равных медианному,
        // 3. элементов больше медианного,
        // и очередь для вывода
        Queue low = new Queue();
        Queue equal = new Queue();
        Queue high = new Queue();
        Queue res = new Queue();

        
        // Заполняем три очереди
        for (int i = 0; i < size; i++)
        {
          int elem = arr.get(i);
          if (elem < middle)
          {
            low.push(elem);
          } else if (elem > middle)
          {
            high.push(elem);
          }
          else
          {
            equal.push(elem);
          }
        }

        
        // Сортируем очереди
        low = sort(low);
        equal = sort(equal);
        high = sort(high);

        
        // Складываем очереди в результирующую
        for (int i = 0; i < low.size(); i++)
        {
          res.push(low.get(i));
        }

        for (int i = 0; i < equal.size(); i++)
        {
          res.push(equal.get(i));
        }
        
        for (int i = 0; i < high.size(); i++)
        {
          res.push(high.get(i));
        }

        return res;
      }
      else
      {
        return arr;
      }
    }
  }
}