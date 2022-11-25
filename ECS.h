#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;

class Entity;

using ComponentID = std::size_t;

//keeps returning next ID
inline ComponentID get_component_id()
{
	static ComponentID last_id = 0;
	return last_id++;
}

//generate new last ID for type ID to set type IDs
template <typename T> inline ComponentID get_component_type_id() noexcept
{
	static ComponentID type_id = get_component_id();
	return type_id;
}

//check if entity has component attached

constexpr std::size_t max_components = 32;

//compares to existing components to see if sufficient
using ComponentBitSet = std::bitset<max_components>;

using ComponentArray = std::array<Component*, max_components>;

class Component
{
public:
	Entity* entity;

	//get access to other components
	virtual void init(){}

	virtual void update(){}
	virtual void draw(){}

	virtual ~Component(){}
};


class Entity
{
private:
	//shows if entity in game
	bool active = true;

	//unique pointers for components that owns and manages entities
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray component_array;
	ComponentBitSet component_bit_set;

public:
	void update()
	{
		for (auto& c : components) c->update();
	}

	void draw()
	{
		for (auto& c : components) c->draw();
	}

	bool is_active() const { return active; }

	//allows unactive entities to be removed
	void destroy() { active = false; }

	template <typename T> bool has_component() const
	{
		//tells if component is attached
		return component_bit_set[get_component_type_id<T>];
	}

	template <typename T, typename... t_args>
	T& add_component(t_args&&... m_args)
	{
		T* c(new T(std::forward<t_args>(m_args)...));
		c->entity = this;
		std::unique_ptr<Component> u_ptr(c);
		components.emplace_back(std::move(u_ptr));
		//new position component always goes to same position in array
		component_array[get_component_type_id<T>()] = c;
		component_bit_set[get_component_type_id<T>()] = true;

		c->init();
		return *c;
	}

	template<typename T> T& get_component() const
	{
		auto ptr(component_array[get_component_type_id<T>()]);
		return *static_cast<T*>(ptr);
	}

	class Manager
	{
	private:
		std::vector<std::unique_ptr<Entity>> entities;

	public:
		

		void update()
		{
			for (auto& e : entities) e->update();
		}

		void draw()
		{
			for (auto& e : entities) e->draw();
		}

		void refresh()
		{
			//remove inactive entities
			entities.erase(std::remove_if(std::begin(entities), std::end(entities),
				[](const std::unique_ptr<Entity>& m_entity)
				{
					return !m_entity->is_active();
				}),
				std::end(entities));
		}

		//adds unique entity with unique_ptr 
		Entity& add_entity()
		{
			auto* e = new Entity();
			std::unique_ptr<Entity> u_ptr{ e };
			entities.emplace_back(std::move(u_ptr));
			return  *e;
		}
	};
};