# Survival Rally: Big Guns
Survival Rally: Big Guns - некоммерческая онлайн игра-гонки с видом сверху, написанная на С++/Qt. 
Активный этап разработки окончен в мае 2021.

Команда:
1) Главный геймдизайнер - @Dima-Makarov
2) Геймдизайнер - @30something
3) Геймдизайнер - @Korbut-Anton
4) Звукорежиссер - @antokir
# Описание
Вооружитесь пулеметом, прихватите мины, выберите машину и едьте в бой!
На выбор есть несколько режимов:
1) Одиночный заезд
2) Игра вдвоем на одном компьютере
3) Игра в локальной сети

В каждый заезд можно добавить 1-6 ботов.

Вы можете также выбрать режим физики, упрощенный или реалистичный, с дрифтами.

На выбор доступно 7 карт.

P.S. Удачи проехать хотя бы 2 круга и выжить в режиме с 6-ю ботами!
# Главное меню
![image](https://user-images.githubusercontent.com/79033065/119549371-d0796b00-bd9f-11eb-9116-c70bf4e0909a.png)
# Выбор режима игры
![image](https://user-images.githubusercontent.com/79033065/119549467-ed15a300-bd9f-11eb-9285-55d1c92f4785.png)
# Сетевая комната
![image](https://user-images.githubusercontent.com/79033065/119550323-f18e8b80-bda0-11eb-8db7-a418487f8c1d.png)
# Игра
![image](https://user-images.githubusercontent.com/79033065/119348516-a479bf00-bca5-11eb-8a91-6d2c85fc8629.png)

# Для игры по сети необходимо:
1) Запустить сервер на любом компьютере в локальной сети 
2) Запустить несколько клиентов
3) На клиентах зайти в пункт "Multiplayer"
4) Ввести IP-адрес, отображаемый на сервере
5) Игрок, подключившийся первым, становится главным: он выбирает карту, количество ботов и т.д.
6) Когда главный игрок нажимает "играть", начинается веселье!
# Как играть
1) Если у вас Windows: 
Скачать архив с игрой, распаковать, наслаждаться
2) Если у вас что-то другое:
Необходимо склонировать репозиторий и скомпилировать проект. Самую большую сложность составляет установка Qt, инструкцию вы можете найти в Интернете. После установки отредактируйте файл cmakelists.txt, изменив там переменную CMAKE_PREFIX_PATH
