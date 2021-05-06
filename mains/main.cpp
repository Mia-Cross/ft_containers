/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemarabe <lemarabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:11:46 by lemarabe          #+#    #+#             */
/*   Updated: 2021/05/06 17:13:23 by lemarabe         ###   ########.fr       */
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
    testQueue();
    testStack();
    testMap();
    testVector();
    // test();
}