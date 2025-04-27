
# C ile Paralel Programlama Örnekleri (Docker + Ubuntu + GCC)

> **Paylaşımlı bellek**, **POSIX semaforları** ve **OpenMP** kullanan basit C örnekleri.  
> Tüm örnekler, Docker ile başlatılan temiz bir Ubuntu konteynerinde derlenip çalıştırılmıştır.

----------

## 📂 Depo Yapısı

Dosya

Amaç

`shared_memory.c`

System V paylaşımlı bellek ile süreçler arası iletişim (IPC) örneği

`semaphore.c`

POSIX adlandırılmış semaforlarla süreç senkronizasyonu örneği

`openmp.c`

OpenMP ile paralel `for` döngüsü ve _reduction_ örneği

----------

## 🛠️ Ön Koşullar

-   **Docker** 20+
    
-   **Git** (depoyu klonlamak / pushlamak için)
    

> Host makinede ek kurulum gerekmez – her şey konteyner içinde yapılır.

----------

## 🚀 Başlarken

```bash
# 1. Ubuntu imajını çekin
docker pull ubuntu:latest

# 2. Masaüstünde bir klasör oluşturun (Windows örneği)
#    C:\~~\~~\Desktop\paralel

# 3. "paralel" adlı konteyneri başlatın ve klasörü bağlayın
#    macOS / Linux kullanıyorsanız yolu kendinize göre değiştirin.
docker run -it --name paralel \
    -v C:\~~\~~\Desktop\paralel:/paralel \
    ubuntu:latest

# 4. Konteyner içinde derleyicileri kurun
apt-get update && apt-get install build-essential -y
```

Üç `.c` dosyasını host’taki `paralel` klasörüne kopyalayın; anında konteynerde `/paralel` altında görünürler.

----------

## 🏗️ Derleme ve Çalıştırma

```bash
cd /paralel

# Paylaşımlı Bellek Örneği
gcc shared_memory.c -o shared_memory.o
./shared_memory.o

# Semafor Örneği
gcc semaphore.c -o semaphore.o
./semaphore.o

# OpenMP Örneği (-fopenmp şart)
gcc -fopenmp openmp.c -o openmp.o
./openmp.o

```

### Örnek Çıktılar

```text
[Child] Data: 1
[Parent] Data: 2

```

![Image](https://github.com/user-attachments/assets/7d6e8638-789b-4ee5-a0f0-74b008a1d98c)

```text
[Child] In critical section
[Child] Exiting critical section
[Parent] In critical section
[Parent] Exiting critical section

```

![Image](https://github.com/user-attachments/assets/14b6cb02-ea9a-4ca4-857b-eebd84f0d2a4)

```text
Thread 0 is adding 0 | sum = 0
Thread 1 is adding 1 | sum = 1
...
Final sum = 45
```

![Image](https://github.com/user-attachments/assets/08e63173-e28a-414c-9d1f-5be0f8688a9d)


----------

## 📦 Temizleme

İşiniz bittiğinde konteyneri durdurup kaldırabilirsiniz:

```bash
docker stop paralel && docker rm paralel
```

----------

### Mahmut Kerem Erden - k.erden03@gmail.com
