#include <iostream>

using namespace std;

class Machine
{
  class State *current;
  public:
    Machine();
    void setCurrent(State *s)
    {
        current = s;
    }
    void idle();
    void sensing();
    void processing();
};

class State
{
  public:
    virtual void idle(Machine *m)
    {
        cout << "   state idle\n";
    }
    virtual void sensing(Machine *m)
    {
        cout << "   state sensing\n";
    }
    virtual void processing(Machine *m)
    {
        cout << "   state processing\n";
    }
};

void Machine::idle()
{
  current->idle(this);
}

void Machine::sensing()
{
  current->sensing(this);
}

void Machine::processing()
{
  current->processing(this);
}

class IDLE: public State
{
  public:
    IDLE()
    {
        cout << "   IDLE-ctor. NEXT STATE: Sensing ";
    };
    ~IDLE()
    {
        cout << "   dtor-IDLE\n";
    };
    void sensing(Machine *m);
};

class SENSING: public State
{
  public:
    SENSING()
    {
        cout << "   SENSING-ctor. NEXT STATE: Processing";
    };
    ~SENSING()
    {
        cout << "   dtor-SENSING\n";
    };
    void processing(Machine *m);

};
class PROCESSING: public State
{
  public:
    PROCESSING()
    {
        cout << "   PROCESSING-ctor. NEXT STATE: Idle ";
    };
    ~PROCESSING()
    {
        cout << "   dtor-PROCESSING\n";
    };
    void idle(Machine *m);

};
void IDLE::sensing(Machine *m)
{
  cout << "  >> going from IDLE to SENSING";
  m->setCurrent(new SENSING());
  delete this;
}

void SENSING::processing(Machine *m)
{
  cout << "  >> going from SENSING to PROCESSING";
  m->setCurrent(new PROCESSING());
  delete this;
}
void PROCESSING::idle(Machine *m)
{
  cout << "  >> going from PROCESSING to IDLE";
  m->setCurrent(new IDLE());
  delete this;
}

Machine::Machine()
{
  current = new IDLE();
  cout << '\n';
}

int main()
{
  void(Machine:: *ptrs[])() =
  {
    Machine::idle, Machine::sensing, Machine::processing
  };
  Machine fsm;
  int num;
  while (1)
  {
    cout << "Enter one of the states: 0 = IDLE, 1 = SENSING, 2= PROCESSING ";
    cin >> num;
    (fsm.*ptrs[num])();
  }
}
