#pragma once
class CTimeManager : public SingleTon<CTimeManager>
{
	friend SingleTon<CTimeManager>;
private:
	CTimeManager();
	virtual ~CTimeManager();

public:
	void			Init();
	void			Update();
	void			Release();

	UINT			GetFPS();
	float			GetDT();

private:
	UINT			fps;	// FPS : �ֻ���(������), 1�ʴ� �׷��� ȭ�� ��
	float			dt;		// Delta Time : �����ð�, 1�����Ӵ� �ҿ�� �ð�

	int				updateCount;
	float			updateOneSecond;
	chrono::high_resolution_clock::time_point prevTime;	// ������������ �ð�
	chrono::high_resolution_clock::time_point curTime;	// ������������ �ð�
};

#define DT			CTimeManager::GetInstance()->GetDT()
#define FPS			CTimeManager::GetInstance()->GetFPS()