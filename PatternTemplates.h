#ifndef PatternTemplatesH
#define PatternTemplatesH



// Шаблонный класс, реализующий паттерн "Итератор"
// (класс абстрактный, так как содержит функции без реализации)

template<typename T> // T - подставляемый тип данных (элемент контейнера)
class Iterator
{
protected:
    Iterator() {}

public:
    virtual ~Iterator() {}
    virtual void First() = 0; // Спозиционироваться на начале контейнера
    virtual void Next() = 0;  // Перейти к следующему элементу
    virtual bool IsDone() const = 0;  // Проверить, достигнут ли конец
    virtual T GetCurrent() const = 0; // Получить текущий элемент
};

template<typename T>
class Container {
public:
    virtual ~Container() = default;
    virtual Iterator<T>* GetIterator() = 0;
};

// Реализация паттерна "Итератор",
// предназначенная для обхода очереди

template<typename T>
class QueueIterator : public Iterator<T>
{
private:
    T* QueueContainer; // Указатель на массив
    size_t Pos; // Текущее положение в массиве
    size_t Size;

public:
    QueueIterator(T* container, int size)
    : QueueContainer(container), Pos(0), Size(size) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= Size); }
    T GetCurrent() const override { return QueueContainer[Pos]; }
};

// Шаблонный класс "Очередь"
const size_t MaxSize = 100;

template <typename T>
class Queue : public Container<T>
{
private:

    T Items[MaxSize];
    size_t Tail;
    size_t Head;

public:

    bool IsEmpty() const { return (Tail == 0); }

    size_t Size() const { return Tail; }


    void Enqueue(T newObject) { Items[Tail++] = newObject; }


    T Dequeue() { return Items[++Head]; }

    T GetElementByIndex(size_t index) const { return Items[index]; }

    Queue() : Tail(0) {}

    virtual Iterator<T> *GetIterator()
    {
        return new QueueIterator<T>(Items, Tail);
    }

};

// Реализация паттерна "Итератор",
// предназначенная для обхода вектора

template<typename T>
class VectorIterator : public Iterator<T>
{
private:
    T* VectorContainer; // Указатель на массив
    size_t Pos; // Текущее положение в массиве
    size_t Size;
public:
    VectorIterator(T *container, int size)
    : VectorContainer(container), Pos(0), Size(size) {}

    void First() override { Pos = 0; }
    void Next() override { Pos++; }
    bool IsDone() const override { return (Pos >= Size); }
    T GetCurrent() const override { return VectorContainer[Pos]; }
};

//Пользовательский Вектор
template <typename T>
class CustomVector : Container<T>
{
private:

    T Items[MaxSize];
    size_t Back_num;
    size_t Front_num;

public:

    size_t Size() const { return Back_num; }

    void Append(T newObject) { Items[Back_num++] = newObject; }

    T Front() { return Items[0]; }

    T Back() { return Items[Back_num]; }

    T operator[](size_t index) const { return Items[index]; }

    T GetElement(size_t index) const { return Items[index]; }


    CustomVector() : Back_num(0), Front_num(0) {}
    virtual Iterator<T> *GetIterator()
    {
        return new VectorIterator<T>(Items, Back_num);
    }

};

// Декоратор для итератора (пустой)

template<typename T>
class IteratorDecorator : public Iterator<T>
{
protected:
    Iterator<T> *It;

public:
    IteratorDecorator(Iterator<T> *it) : It(it) {}
    virtual ~IteratorDecorator() { delete It; }
    virtual void First() { It->First(); }
    virtual void Next() { It->Next(); }
    virtual bool IsDone() const { return It->IsDone(); }
    virtual T GetCurrent() const { return It->GetCurrent(); }
};

// Адаптер для контейнерных классов STL

template<typename ContainerType, typename ItemType>
class ConstIteratorAdapter : public Iterator<ItemType>
{
protected:
    ContainerType *Container;
    typename ContainerType::const_iterator It;

public:
    ConstIteratorAdapter(ContainerType *container)
    : Container(container)
    {
        It = Container->begin();
    }

    virtual ~ConstIteratorAdapter() {}
    virtual void First() { It = Container->begin(); }
    virtual void Next() { It++; }
    virtual bool IsDone() const { return (It == Container->end()); }
    virtual ItemType GetCurrent() const { return *It; }
};



#endif // PatternTemplatesH
