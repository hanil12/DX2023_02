#pragma once
class World
{
public:
	World();
	~World();

	void Update();

	bool End();

private:
	shared_ptr<Creature> _boss;
	vector<shared_ptr<Creature>> _players;
};

