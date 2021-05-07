/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:11:46 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/07 15:42:57 by lemarabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

bool isOdd(int x);
bool isDigit(int x);
bool compareAbs(int x, int y);
bool isNear(int x, int y);

void testList();
void testMap();
void testQueue();
void testStack();
void testVector();
// void test();

int main()
{
    testList();
    testStack();
    testQueue();
    testVector();
    testMap();
    // test();
}