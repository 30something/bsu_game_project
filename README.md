# Project_name (Death Rally, Survival Rally, etc.)
project_name - некоммерческая онлайн игра-гонки с видом сверху, написанная на С++/Qt. 
Активный этап разработки окончен в мае 2021.

Команда:
1) главный геймдизайнер - @Dima-Makarov
2) геймдизайнер - @30something
3) геймдизайнер - @Korbut-Anton
4) звукорежиссер - @antokir
# Описание
Вооружитесь пулеметом, прихватите мины, выберите машину и едьте в бой!
На выбор есть несколько режимов:
1) одиночный заезд
2) игра вдвоем на одном компьютере
3) игра в локальной сети

В каждый заезд можно добавить 1-6 ботов.

Вы можете также выбрать режим физики, упрощенный или реалистичный, с дрифтами.

На выбор доступно 7 карт.

P.S. Удачи проехать хотя бы 2 круга и выжить в режиме с 6-ю ботами!
# Главное меню
![image](https://user-images.githubusercontent.com/79033065/119272107-1651fa00-bc0d-11eb-9492-329b76e8f4b0.png)
# Выбор режима игры
![image](https://user-images.githubusercontent.com/79033065/119272119-2b2e8d80-bc0d-11eb-8ddf-bd259dc0d66e.png)
# Сетевая комната
![image](https://user-images.githubusercontent.com/79033065/119272179-7052bf80-bc0d-11eb-81c7-b8c9074a2520.png)
# Игра
![image](https://user-images.githubusercontent.com/79033065/119272478-c4aa6f00-bc0e-11eb-9376-d1505845d3e5.png)

# Для игры по сети необходимо:
1) Запустить сервер на любом компьютере в локальной сети 
2) Запустить несколько клиентов
3) На клиентах зайти в пункт "мультиплеер"
4) Ввести IP-адрес, отображаемый на сервере
5) Игрок, подключившийся первым, становится главным: он выбирает карту, количество ботов и т.д.
6) Когда главный игрок нажимает "играть", начинается веселье!
# Как играть
1) Если у вас Windows: 
Скачать архив с игрой, распаковать, наслаждаться
2) Если у вас что-то другое:
Необходимо склонировать репозиторий и скомпилировать проект. Самую большую сложность составляет установка Qt, инструкцию вы можете найти в Интернете. После установки, отредактируйте файл cmakelists.txt, изменив там переменную CMAKE_PREFIX_PATH
