#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>

#include "Menu.h"
//#include "sortingAlgorithms.h"

class visualizer
{
	sf::RenderWindow m_window;
	sf::Event m_event;
	sf::SoundBuffer m_buffer;
	sf::SoundBuffer m_buffer1;
	sf::SoundBuffer m_buffer2;
	sf::Sound m_sound;
	sf::Sound sound1;
	sf::Sound sound2;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Vector2f m_ogSize;
	sf::Vector2u m_windowSize;

	std::vector<int> m_nums;
	const int m_numCount = 100;
	
	Menu m_menu;

	bool m_sorted = false;
	bool m_running = true;
	
	void loadSound();
	void resizeWindow(const float width, const float height);
	void loadTexture();

	int partition(std::vector<int>& arr, int low, int high);
	void merge(std::vector<int>& arr, int p, int q, int r);
	void sortVisualizer(const std::vector<int>& arr, const int index1, const int index2);

	void bubbleSort(std::vector<int>& arr);
	void selectionSort(std::vector<int>& arr);
	void insertionSort(std::vector<int>& arr);
	void quickSort(std::vector<int>& arr, int low, int high);
	void mergeSort(std::vector<int>& arr, int l, int r);


	void feedArr();
	void sUserInput();
	void sRender();

public:
	bool m_freezeWindow = false;
	visualizer();
	void run();
};

