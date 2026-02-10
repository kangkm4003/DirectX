#pragma once

//namespace SharedPtr
//{
//	class Object;
//	class Component
//	{
//	public:
//		~Component() { cout << "Component 소멸!\n"; }
//
//		weak_ptr<Object> owner;
//
//		void Update()
//		{
//			owner.expired(); // lock()과는 다르게 expired는 반환값이 bool 이다
//
//			if (auto lockedOwner = owner.lock()) //weak_ptr 의 lock() 매서드를 사용하면 그에대한 shared_ptr을 반환해준다 (유효하지 않다면 nullptr 반환)
//			{
//				lockedOwner;
//			}
//			else
//			{
//				lockedOwner.reset(); //nullptr 을 반환 했다면 자신 또한 해제
//			}
//		}
//	};
//};

class Scene;

class Program
{
public:
	Program();
	~Program();

	void SetGlobalBuffers();

	void Init();
	void Update();
	void Render();

private:
	void SwitchScene(int index);

	unique_ptr<ViewProjectionBuffer> VPBuffer;

	Matrix view, projection;

	vector<shared_ptr<Scene>> sceneList;
	shared_ptr<Scene> currentScene;
};
