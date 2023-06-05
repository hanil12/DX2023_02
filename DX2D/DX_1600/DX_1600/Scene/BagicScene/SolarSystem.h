#pragma once
class Planet;

class SolarSystem : public Scene
{
public:
	SolarSystem();
	virtual ~SolarSystem();

	virtual void Update() override;
	virtual void Render() override;

private:
	shared_ptr<Planet> _sun;
	shared_ptr<Planet> _earth;
	shared_ptr<Planet> _moon;
};

