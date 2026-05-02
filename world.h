#pragma once
#include <cstdint>
#include <cassert>
#include <vector>
#include <queue>
#include <unordered_map>
#include <bitset>
#include <memory>
#include <typeindex>
#include <algorithm>

using Entity = std::int32_t;
using ComponentId = std::uint8_t;
const ComponentId MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

class EntityManager
{
	std::vector<Signature> signatures_; // extends only
	std::queue<Entity> reusable_entities_; // reuse released entities

	Entity CreateEntity()
	{
        if (reusable_entities_.size()) {
            Entity id = reusable_entities_.front();
            reusable_entities_.pop();
            return id;
        }

        signatures_.push_back(Signature());
        return Entity(signatures_.size() - 1);
	}

	void ReleaseEntity(Entity entity)
	{
        assert(entity < signatures_.size() && "Release non-existent entity");
        reusable_entities_.push(entity);
        signatures_[entity].reset();
	}

	void SetSignature(Entity entity, Signature signature)
	{
        assert(entity < signatures_.size() && "Set signature for non-existent entity");
        signatures_[entity] = signature;
	}

	Signature GetSignature(Entity entity)
	{
        assert(entity < signatures_.size() && "Get signature from non-existent entity");
        return signatures_[entity];
	}
};

class IComponentArray
{
    friend class ComponentManager;
protected:
	ComponentId id_;
	IComponentArray(Component id) : id_(id) { }
	virtual ~IComponentArray() = default;
	virtual void OnEntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray
{
    friend class ComponentManager;

    std::vector<T> components_;
    std::vector<int32_t> etoi_;
    std::queue<int32_t> reusable_indices_;

	void Insert(Entity entity, T component)
	{
		etoi_.reserve(entity+1);
		etoi_.resize(etoi_.capacity(), -1);

        assert(etoi_[entity] == -1 && "Same component added to same entity more than once");

		if (reusable_indices_.size()) {
            index = reusable_indices_.front();
            reusable_entities_.pop();
			components_[index] = component;
			etoi_[entity] = index;
        }
		else {
			components_.push_back(component);
			etoi_[entity] = components_.size() - 1;
		}
	}

	void Remove(Entity entity)
	{
        assert(entity < etoi_.size() && etoi_[entity] != -1 && "Removing non-existent component from entity");
		reusable_entities_.push(etoi_[entity]);
		etoi_[entity] = -1;
	}

	T& Get(Entity entity)
	{
        assert(entity < etoi_.size() && etoi_[entity] != -1 && "Getting non-existent component from entity");
        return components_[etoi_[entity]]; 
	}

	void OnEntityDestroyed(Entity entity) override
	{
        if (entity < etoi_.size() && etoi_[entity] != -1)
            Remove(entity);
	}
};

class ComponentManager
{
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> arrays_;
	ComponentId largest_id_{};

	template<typename T>
	std::shared_ptr<ComponentArray<T>> GetArray()
	{
		auto it = arrays_.find(typeid(T));
		assert(it != arrays_.end() && "Component not registered before use");
		return std::static_pointer_cast<ComponentArray<T>>(it->second);
	}

	template<typename T>
	void RegisterComponent()
	{
		assert(largest_id_ < MAX_COMPONENTS && "Too many component types");
        assert(arrays_.find(typeid(T)) == arrays_.end() && "Registering component more than once");
        arrays_.insert({typeid(T), std::make_shared<ComponentArray<T>>(largest_id_++)});
	}

	template<typename T>
	ComponentId GetComponentId()
	{
		return GetArray<T>()->id_;
	}

	template<typename T>
	void AddComponent(Entity entity, T component)
	{
        GetArray<T>()->Insert(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
        GetArray<T>()->Remove(entity);
	}

	template<typename T>
	T& GetComponent(Entity entity)
	{
        return GetArray<T>()->Get(entity);
	}

	void OnEntityDestroyed(Entity entity)
	{
        for (auto const& pair : arrays_) {
			auto const& component = pair.second;
			component->OnEntityDestroyed(entity);
		}
	}
};

class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> RegisterSystem()
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

		// Create a pointer to the system and return it so it can be used externally
		auto system = std::make_shared<T>();
		mSystems.insert({typeName, system});
		return system;
	}

	template<typename T>
	void SetSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

		// Set the signature for this system
		mSignatures.insert({typeName, signature});
	}

	void EntityDestroyed(Entity entity)
	{
		// Erase a destroyed entity from all system lists
		// mEntities is a set so no check needed
		for (auto const& pair : mSystems)
		{
			auto const& system = pair.second;

			system->mEntities.erase(entity);
		}
	}

	void EntitySignatureChanged(Entity entity, Signature entitySignature)
	{
		// Notify each system that an entity's signature changed
		for (auto const& pair : mSystems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mSignatures[type];

			// Entity signature matches system signature - insert into set
			if ((entitySignature & systemSignature) == systemSignature)
			{
				system->mEntities.insert(entity);
			}
			// Entity signature does not match system signature - erase from set
			else
			{
				system->mEntities.erase(entity);
			}
		}
	}

private:
	// Map from system type string pointer to a signature
	std::unordered_map<const char*, Signature> mSignatures{};

	// Map from system type string pointer to a system pointer
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};