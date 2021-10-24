using System;
using System.Collections.Generic;

namespace Hoar
{
  public class Queue
  {
    private List<int> arr;
    public Queue()
    {
      this.arr = new List<int>();
    }

    public bool empty()
    {
      if (arr.Count == 0)
        return true;
      else return false;
    }

    public void push(int element)
    {
      arr.Add(element);
    }

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

    public Queue sort(Queue arr)
    {
      int size = arr.size();
      Queue low = new Queue();
      Queue high = new Queue();
      Queue equal = new Queue();
      Queue res = new Queue();

      if (size > 1)
      {
        int middle = arr.get(size / 2);

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

        low = sort(low);
        equal = sort(equal);
        high = sort(high);

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