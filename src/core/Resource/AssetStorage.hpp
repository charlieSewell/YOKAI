#pragma once
#include <unordered_map>
#include <mutex>
struct IAssetStorage {
    public:
        virtual ~IAssetStorage() = default;
};

template <typename T>
struct AssetStorage : public IAssetStorage{
    AssetStorage(std::function<bool(std::recursive_mutex&, std::shared_ptr<T>&, const std::string&)> loadFunc): loadFromFile(loadFunc){}
    std::function<bool(std::shared_ptr<T>&, const std::string&)> loadFromFile;
    std::unordered_map<std::string, std::weak_ptr<T>> m_assets;
    std::recursive_mutex m_lock;
};