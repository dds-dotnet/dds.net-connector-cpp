#include "src/internal/inc/buffer_manager.h"

#include <memory.h>

#define BYTES_IN_1K   1024
#define BYTES_IN_1M   BYTES_IN_1K * BYTES_IN_1K


dds::net::connector::_internal::BufferManager::BufferManager()
{
}

void* dds::net::connector::_internal::BufferManager::get1k()
{
  return get(BYTES_IN_1K * 1);
}

void* dds::net::connector::_internal::BufferManager::get2k()
{
  return get(BYTES_IN_1K * 2);
}

void* dds::net::connector::_internal::BufferManager::get4k()
{
  return get(BYTES_IN_1K * 4);
}

void* dds::net::connector::_internal::BufferManager::get8k()
{
  return get(BYTES_IN_1K * 8);
}

void* dds::net::connector::_internal::BufferManager::get16k()
{
  return get(BYTES_IN_1K * 16);
}

void* dds::net::connector::_internal::BufferManager::get32k()
{
  return get(BYTES_IN_1K * 32);
}

void* dds::net::connector::_internal::BufferManager::get64k()
{
  return get(BYTES_IN_1K * 64);
}

void* dds::net::connector::_internal::BufferManager::get128k()
{
  return get(BYTES_IN_1K * 128);
}

void* dds::net::connector::_internal::BufferManager::get256k()
{
  return get(BYTES_IN_1K * 256);
}

void* dds::net::connector::_internal::BufferManager::get512k()
{
  return get(BYTES_IN_1K * 512);
}

void* dds::net::connector::_internal::BufferManager::get1M()
{
  return get(BYTES_IN_1M * 1);
}

void* dds::net::connector::_internal::BufferManager::get2M()
{
  return get(BYTES_IN_1M * 2);
}

void* dds::net::connector::_internal::BufferManager::get4M()
{
  return get(BYTES_IN_1M * 4);
}

void* dds::net::connector::_internal::BufferManager::get8M()
{
  return get(BYTES_IN_1M * 8);
}

void* dds::net::connector::_internal::BufferManager::get16M()
{
  return get(BYTES_IN_1M * 16);
}

void* dds::net::connector::_internal::BufferManager::get32M()
{
  return get(BYTES_IN_1M * 32);
}

void* dds::net::connector::_internal::BufferManager::get64M()
{
  return get(BYTES_IN_1M * 64);
}

void* dds::net::connector::_internal::BufferManager::get(int size)
{
  buffLock.lock();

  void* ret = nullptr;

  for (BufferDefinition& buff : buffers)
  {
    if (buff.size == size &&
        buff.isFree == true)
    {
      buff.isFree = false;
      ret = buff.address;
      break;
    }
  }

  if (ret == nullptr)
  {
    BufferDefinition newBuffer;

    newBuffer.address = malloc(size);
    newBuffer.size = size;
    newBuffer.isFree = false;

    ret = newBuffer.address;

    buffers.push_back(newBuffer);
  }

  buffLock.unlock();

  return ret;
}

void dds::net::connector::_internal::BufferManager::free(void* freeBuffer)
{
  buffLock.lock();

  for (BufferDefinition& buff : buffers)
  {
    if (buff.address == freeBuffer)
    {
      buff.isFree = true;
      break;
    }
  }

  buffLock.unlock();
}

void dds::net::connector::_internal::BufferManager::GC()
{
  buffLock.lock();

  std::list<BufferDefinition> unused;

  for (BufferDefinition& buff : buffers)
  {
    if (buff.isFree == true)
    {
      ::free(buff.address);
      unused.push_back(buff);
    }
  }

  for (BufferDefinition& buff : unused)
  {
    buffers.remove_if(
      [&](const BufferDefinition& b)
      {
        return b.address == buff.address;
      });
  }

  unused.clear();

  buffLock.unlock();
}
