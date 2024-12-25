#pragma once

#include <memory>

class VAO {
public:
    VAO();
    void Bind() const;
    void Delete() const;
    [[nodiscard]] static std::shared_ptr<VAO> Create();
    static void Unbind();
    static void SetFloat(std::uint32_t index, std::int32_t stride, const void *pointer);
    static void SetVec2(std::uint32_t index, std::int32_t stride, const void *pointer);
    static void SetVec3(std::uint32_t index, std::int32_t stride, const void *pointer);

private:
    std::uint32_t mID = 0;
};
