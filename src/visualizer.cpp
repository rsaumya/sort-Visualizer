#include "visualizer.h"

visualizer::visualizer() : m_window(sf::VideoMode(1280.0f, 720.0f), "Sort Visualizer"),
m_menu(m_window.getSize().x, m_window.getSize().y) {
    feedArr();
    loadSound();
    loadTexture();
}

void visualizer::loadSound()
{
    if (!m_buffer.loadFromFile("Sounds/menu.wav"))
    {
        std::cout << "Unable to load sound from file!\n";
        exit(EXIT_FAILURE);
    }
    m_sound.setBuffer(m_buffer);
    if (!m_buffer1.loadFromFile("Sounds/beep.wav")) { std::cout << "Unable to load sound\n"; }
    sound1.setBuffer(m_buffer1);

    if (!m_buffer2.loadFromFile("Sounds/beep1.wav")) { std::cout << "Unable to load sound\n"; }
    sound2.setBuffer(m_buffer2);
}

void visualizer::loadTexture()
{
    if (!m_texture.loadFromFile("background.png"))
    {
        std::cout << "Unable to load background file!\n";
        exit(EXIT_FAILURE);
    }
    m_sprite.setTexture(m_texture);
    float scaleX = m_window.getView().getSize().x / m_texture.getSize().x;
    float scaleY = m_window.getView().getSize().y / m_texture.getSize().y;
    m_sprite.setScale(scaleX, scaleY);
}

void visualizer::resizeWindow(const float width, const float height)
{
    //set new size of window
    m_window.setSize(sf::Vector2u(width, height));
}

void visualizer::sortVisualizer(const std::vector<int>& arr, const int index1,const int index2)
{
    m_window.clear();

    float width = static_cast<float>(m_window.getSize().x) / arr.size();
    for (size_t i = 0; i < arr.size(); i++)
    {
        sf::RectangleShape rectangle(sf::Vector2f(width - 2, static_cast<float>(arr[i])));
        rectangle.setPosition(i * width, m_window.getSize().y - arr[i]);
        rectangle.setFillColor(sf::Color::Blue);
        if (i == index1)
        {
            rectangle.setFillColor(sf::Color::Red);
            sound1.setVolume(arr[i] / 6);
            sound1.play();
        }
        if (i == index2)
        {
            rectangle.setFillColor(sf::Color::Green);
            sound2.setVolume(arr[i] / 6);
            sound2.play();
        }
        m_window.draw(rectangle);
    }
    m_window.display();
    sf::Event event;
    sf::sleep(sf::milliseconds(150));
    sUserInput();
}

int visualizer::partition(std::vector<int>& arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            std::swap(arr[i], arr[j]);
            if (!m_running) { return -1; }
            sortVisualizer(arr, i, j);

        }
    }
    std::swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void visualizer::merge(std::vector<int>& arr, int p, int q, int r)
{
    if (!m_running) { return; }

    int n1 = (q - p + 1);
    int n2 = (r - q);

    std::vector<int> L(n1), M(n2);

    for (int i = 0; i < n1; i++) { L[i] = arr[p + i]; }
    for (int j = 0; j < n2; j++) { M[j] = arr[q + 1 + j]; }

    int i, j, k;
    i = 0;
    j = 0;
    k = p;

    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])
        {
            arr[k] = L[i];
            sortVisualizer(arr, k, i);
            if (!m_running) { return; }
            i++;
        }
        else
        {
            arr[k] = M[j];
            sortVisualizer(arr, k, j);
            if (!m_running) { return; }
            j++;

        }

        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
        sortVisualizer(arr, k, i);
        if (!m_running) { return; }
    }
    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
        sortVisualizer(arr, k, j);
        if (!m_running) { return; }
    }
}

void visualizer::bubbleSort(std::vector<int>& arr)
{
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++)
    {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                sortVisualizer(arr, j, j + 1);
                if (!m_running) { return; }
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }

}

void visualizer::selectionSort(std::vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
        sortVisualizer(arr, i, minIndex);
        if (!m_running) { return; }
    }
}

void visualizer::insertionSort(std::vector<int>& arr)
{
    int n = arr.size();
    for (int i = 1; i < n; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        sortVisualizer(arr, j + 1, key);
        if (!m_running) { return; }
    }
}

void visualizer::quickSort(std::vector<int>& arr, int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        if (!m_running) { return; }
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void visualizer::mergeSort(std::vector<int>& arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        if (!m_running) { return; }
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);

    }
}


void visualizer::feedArr()
{
    m_nums.clear();
    for (int i = 0; i < m_numCount; i++)
    {
        m_nums.push_back(std::rand() % 500 + 50);
    }
}

void visualizer::sRender()
{
    m_window.clear();
    m_window.draw(m_sprite);
    
    m_menu.draw(m_window);
   
    m_window.display();
}

void visualizer::sUserInput()
{
    
    while (m_window.pollEvent(m_event))
    {
        if (m_event.type == sf::Event::Closed) 
        {
            m_window.close();
            exit(EXIT_SUCCESS);
        }
        
        if (m_event.type == sf::Event::Resized)
        {
            resizeWindow(m_event.size.width, m_event.size.height);
        }

        if ((m_event.type == sf::Event::KeyPressed) && (m_event.key.code == sf::Keyboard::Escape))
        {
            sound1.stop();
            sound2.stop();
            m_running = false;
        }
        

        // Check for key press events
        if (m_event.type == sf::Event::KeyPressed)
        {
           if (m_event.key.code == sf::Keyboard::Up)
            {
                m_menu.MoveUp();
                m_sound.play();
            }
            else if (m_event.key.code == sf::Keyboard::Down)
            {
                m_menu.MoveDown();
                m_sound.play();
            }
            else if (m_event.key.code == sf::Keyboard::Enter)
            {
               m_running = true;
                switch (m_menu.GetPressedItem())
                {
                case 0:
                    bubbleSort(m_nums);
                    m_freezeWindow = true;
                    m_sorted = true; // Set flag to start sorting
                    break;
                case 1:
                    insertionSort(m_nums);
                    m_freezeWindow = true;
                    m_sorted = true; // Set flag to start sorting
                    break;
                case 2:
                    selectionSort(m_nums);
                    m_freezeWindow = true;
                    m_sorted = true; // Set flag to start sorting
                    break;
                case 3:
                    quickSort(m_nums,0, m_nums.size()-1);
                    m_freezeWindow = true;
                    m_sorted = true; // Set flag to start sorting
                    break;
                case 4:
                    mergeSort(m_nums,0, m_nums.size()-1);
                    m_freezeWindow = true;
                    m_sorted = true; // Set flag to start sorting
                    break;
                case 5:
                    m_window.close();
                    exit(EXIT_SUCCESS);
                    break;
                }

            }


        }
    }

}

void visualizer::run()
{
    while (m_window.isOpen())
    {
        sUserInput();
        sRender();
        
        if (m_sorted )
        {
            feedArr();
            m_sorted = false;
        }
    }
}