class ISubscriber
{
public:
	virtual void notify() = 0;
};

class ISubject
{
public:
	virtual void add(ISubscriber* _subscriber) = 0;
	virtual void remove(ISubscriber* _subscriber) = 0;
	virtual void notify() = 0;
};

int main()
{
	return 0;
}