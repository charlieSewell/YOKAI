#pragma once
#include <unordered_map>
#include "AssetStorage.hpp"
#include <typeinfo>
#include <mutex>
class AssetProxy
{
    public:
        AssetProxy() = default;
        
        template < typename T>
        void AddStorage(std::function<bool(std::recursive_mutex&, std::shared_ptr<T>&, const std::string&)> assetLoadingFunction)
        {
            const size_t typeID = typeid(AssetStorage<T>).hash_code();
            m_storages.emplace(typeID, std::make_unique<AssetStorage<T>>(assetLoadingFunction));
        }
        template < typename T>
        std::shared_ptr<T> GetAsset(const std::string &pathName)
        {
            auto& storage = GetStorage<T>();
            
            auto element = storage.m_assets.find(pathName);
            if(element != std::end(storage.m_assets))
            {
                return std::shared_ptr<T>(element->second);
            }
            else 
            {
                std::shared_ptr<T> newObject;
                storage.loadFromFile(newObject, pathName);
                storage.m_assets.emplace(pathName, newObject);
                return newObject;
            }
            
        }
        
    private:
        template <typename T>
        AssetStorage<T>& GetStorage()
        {
            const size_t typeID = typeid(AssetStorage<T>).hash_code();
            auto it = m_storages.find(typeID);
            if(it != m_storages.end())
            {
                throw new std::exception("Storage not found! Maybe you need to add a storage for this type");
            }
            return (static_cast<AssetStorage<T>&>(*it->second.get()));
        }
        std::unordered_map<size_t, std::unique_ptr<IAssetStorage>> m_storages;
};