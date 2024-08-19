#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 *
 * @tparam T O tipo dos dados armazenados na lista.
 */
using namespace std;
template<typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
public:
    /**
     * @brief Destrutor. Destroi todos os elementos da lista
     */
    virtual ~MinhaListaEncadeada() {

        while (!vazia())
        {
            removerDoInicio();
        }

    }

    /**
     * @brief Obt�m a quantidade de itens na lista.
     *
     * @return Um inteiro maior ou igual a 0.
     */
    virtual std::size_t tamanho() const
    {
        return this->_tamanho;
    };

    /**
     * @brief Indica se h� algum item na lista ou n�o.
     *
     * @return false se houver algum item na lista; true caso contr�rio.
     */
    virtual bool vazia() const
    {
        if (this->_tamanho > 0)
        {
            return false;
        }
        else
        {
            return true;
        }
    };

    /**
     * @brief Obt�m a posi��o de um item na lista. Lan�a
     * ExcecaoListaEncadeadaVazia caso a lista esteja vazia ou
     * ExcecaoDadoInexistente caso o item n�o esteja contido na lista.
     *
     * @param dado O item cuja posi��o deseja-se obter.
     * @return Um inteiro na faixa [0, tamanho); se houver mais que um mesmo
     * item na lista, a posi��o da primeira ocorr�ncia.
     */
    virtual std::size_t posicao(T dado) const
    {
        int posicao = 0;
        Elemento<T>* elem_atual = this->_primeiro;

        if (vazia() == true)
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        if (contem(dado) == false)
        {
            throw ExcecaoDadoInexistente();
        }
        while (elem_atual != nullptr)
        {
            if (elem_atual->dado == dado)
            {
                return posicao;
            }
            posicao++;
            elem_atual = elem_atual->proximo;

        }

        return 0;
    };



    /**
     * @brief Indica se um dado item est� contido na lista ou n�o.
     *
     * @param dado O item sendo buscado.
     * @return true se o item est� contido na lista; false caso contr�rio.
     */
    virtual bool contem(T dado) const
    {

        Elemento<T>* elementocontido = this->_primeiro;

        while (elementocontido != nullptr)
        {
            if (elementocontido->dado == dado)
            {
                return true;
            }
            elementocontido = elementocontido->proximo;
        }
        return false;
    };



    /**
     * @brief Insere um item no in�cio da lista.
     *
     * @param dado O item sendo inserido.
     */
    virtual void inserirNoInicio(T dado)
    {

        if (this->_primeiro == nullptr)
        {
            Elemento<T>* novoelemento = new Elemento<T>(dado, this->_primeiro);
            this->_primeiro = novoelemento;
        }
        else {
            Elemento<T>* novoelemento = new Elemento<T>(dado, this->_primeiro);
            novoelemento->proximo = this->_primeiro;
            this->_primeiro = novoelemento;
        }
        this->_tamanho++;


    };

    /**
     * @brief Insere um item em uma posi��o espec�fica da lista. Lan�a
     * ExcecaoPosicaoInvalida caso a posi��o n�o esteja na faixa
     * [0, tamanho].
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho]. Ao se inserir em
     * uma posi��o j� ocupada, a posi��o do item que j� estava naquela posi��o
     * ser� posicao + 1; inserir-se na posicao tamanho significa inserir-se no
     * fim da lista.
     * @param dado O item sendo inserido.
     */
    virtual void inserir(std::size_t posicao, T dado)
    {


        if (posicao > tamanho())
        {
            throw ExcecaoPosicaoInvalida();
        }
        else if (posicao == 0)
        {
            inserirNoInicio(dado);

        }
        else if (posicao == tamanho())
        {
            inserirNoFim(dado);
        }

        else {

            Elemento<T>* elem_atual = this->_primeiro;

            for (size_t i = 0; i < posicao - 1; i++)
            {
                elem_atual = elem_atual->proximo;
            }

            Elemento<T>* elem_inserir = new Elemento<T>(dado, elem_atual->proximo);

            elem_atual->proximo = elem_inserir;


            this->_tamanho++;
        }
    };




    /**
     * @brief Insere um item no fim da lista.
     *
     * @param dado O item sendo inserido.
     */

    virtual void inserirNoFim(T dado)
    {

        if (vazia() == true)
        {
            Elemento<T>* ultimoelemento = new Elemento<T>(dado);
            this->_primeiro = ultimoelemento;
        }
        else {
            Elemento<T>* ultimoelemento = new Elemento<T>(dado);
            Elemento<T>* elem_atual = this->_primeiro;

            while (elem_atual->proximo != nullptr)
            {
                elem_atual = elem_atual->proximo;
            }
            elem_atual->proximo = ultimoelemento;
        }
        this->_tamanho++;

    };

    /**
     * @brief Remove o primeiro item da lista. Lan�a ExcecaoListaEncadeadaVazia
     * caso n�o haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoInicio()
    {
        Elemento<T>* elem_atual = this->_primeiro;

        if (vazia() == true)
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        else {
            T dadoremovido = elem_atual->dado;
            this->_primeiro = elem_atual->proximo;

            delete elem_atual;
            this->_tamanho--;

            return T(dadoremovido);
        }
    };

    /**
     * @brief Remove um item de uma posi��o espec�fica da lista. Lan�a
     * ExcecaoPosicaoInvalida caso a posi��o n�o esteja na faixa [0, tamanho).
     *
     * @param posicao Um inteiro dentro da faixa [0, tamanho).
     * @return O item removido.
     */
    virtual T removerDe(std::size_t posicao)
    {
        Elemento<T>* elem_atual = this->_primeiro;

        if (posicao >= tamanho())
        {
            throw ExcecaoPosicaoInvalida();
        }
        else if (posicao == 0)
        {
            return removerDoInicio();

        }
        else if (posicao == tamanho() - 1)
        {
            return removerDoFim();
        }
        else {
            for (size_t i = 0; i < posicao - 1; i++)
            {
                elem_atual = elem_atual->proximo;
            }

            Elemento<T>* elem_proximo = elem_atual->proximo->proximo;
            T dadoremovido = elem_atual->proximo->dado;
            delete elem_atual->proximo;
            elem_atual->proximo = elem_proximo;
            this->_tamanho--;

            return T(dadoremovido);
        }
    };

    /**
     * @brief Remove o �ltimo item da lista. Lan�a ExcecaoListaEncadeadaVazia
     * caso n�o haja nenhum item na lista.
     *
     * @return O item removido.
     */
    virtual T removerDoFim()
    {
        Elemento<T>* elem_atual = this->_primeiro;

        if (vazia() == true)
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        if (elem_atual->proximo == nullptr)
        {

            T dadoremovido = elem_atual->dado;
            delete elem_atual;
            this->_primeiro = nullptr;
            this->_tamanho--;
            return T(dadoremovido);
        }

        else {
            for (size_t i = 0; i < this->_tamanho - 2; i++)
            {
                elem_atual = elem_atual->proximo;
            }

            T dadoremovido = elem_atual->proximo->dado;
            delete elem_atual->proximo;
            elem_atual->proximo = nullptr;
            this->_tamanho--;

            return T(dadoremovido);
        }
    };

    /**
     * @brief Remove um item espec�fico da lista. Lan�a
     * ExcecaoListaEncadeadaVazia caso n�o haja nenhum item na lista ou
     * ExcecaoDadoInexistente caso o item n�o esteja contido na lista.
     *
     * @param dado O item a ser removido. Se houver mais que um item com
     * o mesmo valor, remove a primeira ocorr�ncia.
     */
    virtual void remover(T dado)
    {
        Elemento<T>* penultimo_elem = nullptr;
        Elemento<T>* elem_atual = this->_primeiro;

        if (vazia() == true)
        {
            throw ExcecaoListaEncadeadaVazia();
        }
        if (contem(dado) == false)
        {
            throw ExcecaoDadoInexistente();
        }

        else if (elem_atual->dado == dado)
        {
            this->_primeiro = elem_atual->proximo;

        }
        else {
            while (elem_atual->dado != dado)
            {
                penultimo_elem = elem_atual;
                elem_atual = elem_atual->proximo;
            }

            penultimo_elem->proximo = elem_atual->proximo;



        }
        delete elem_atual;
        this->_tamanho--;
    };
};

#endif