#pragma once

//namespace SharedPtr
//{
//	class Object;
//	class Component
//	{
//	public:
//		~Component() { cout << "Component �Ҹ�!\n"; }
//
//		weak_ptr<Object> owner;
//
//		void Update()
//		{
//			owner.expired(); // lock()���� �ٸ��� expired�� ��ȯ���� bool �̴�
//
//			if (auto lockedOwner = owner.lock()) //weak_ptr �� lock() �ż��带 ����ϸ� �׿����� shared_ptr�� ��ȯ���ش� (��ȿ���� �ʴٸ� nullptr ��ȯ)
//			{
//				lockedOwner;
//			}
//			else
//			{
//				lockedOwner.reset(); //nullptr �� ��ȯ �ߴٸ� �ڽ� ���� ����
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
