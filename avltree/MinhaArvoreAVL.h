#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

using namespace std;

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
private:
    
    void destrutor_arvore(Nodo<T>* nodo) { 

        if (nodo != nullptr) {

            destrutor_arvore(nodo->filhoEsquerda);
            
            destrutor_arvore(nodo->filhoDireita);

            delete nodo;
        
        }
    }

   
    int aux_quant(Nodo<T>* nodo) const {

        if (nodo == nullptr) {

            return 0;

        }

        else {

            return 1 + aux_quant(nodo->filhoEsquerda) + aux_quant(nodo->filhoDireita);

        }
    }
    
    
    Nodo<T>* achar_nodo(Nodo<T>* nodo, T chave) const {

        if (nodo == nullptr) {

            return nullptr;

        }

        if (chave == nodo->chave) {

            return nodo;

        }

        if (chave < nodo->chave) {

            return achar_nodo(nodo->filhoEsquerda, chave);

        }

        else {

            return achar_nodo(nodo->filhoDireita, chave);
        }
    }
    
    
    int valor_altura(Nodo<T>* nodo) const {
        
        if (nodo != nullptr)
        {
            return nodo->altura;
        }
        
        else {
            
            return -1;
        
        }
    }

    void atualizar_altura(Nodo<T>* nodo) {
        
        if (nodo != nullptr) {

            int altura_esq, altura_dir;
                
            altura_esq = valor_altura(nodo->filhoEsquerda);
            
            altura_dir = valor_altura(nodo->filhoDireita);

            if (altura_dir > altura_esq)
            {
                nodo->altura = 1 + altura_dir;
            }

            else {

                nodo->altura = 1 + altura_esq;
            }
        }
    }


    int valor_balanceamento(Nodo<T>* nodo) const {
       
        if (nodo == nullptr)
        {
            return 0;
        }
        else
        {
            return valor_altura(nodo->filhoEsquerda) - valor_altura(nodo->filhoDireita);
        }
    }

        
        
    Nodo<T>* rotacao_dir(Nodo<T>* nodo) { 
        
        Nodo<T>* filho_esq = nodo->filhoEsquerda;
        Nodo<T>* dir_filhoesq = filho_esq->filhoDireita;

        filho_esq->filhoDireita = nodo;
        nodo->filhoEsquerda = dir_filhoesq;

        atualizar_altura(nodo);
        atualizar_altura(filho_esq);

        return filho_esq;
    }

        
    
    Nodo<T>* rotacao_esq(Nodo<T>* nodo) { 
        
        Nodo<T>* filho_dir = nodo->filhoDireita;
        Nodo<T>* esq_filhodir = filho_dir->filhoEsquerda;

        filho_dir->filhoEsquerda = nodo;
        nodo->filhoDireita = esq_filhodir;

        atualizar_altura(nodo);
        atualizar_altura(filho_dir);

        return filho_dir;
    
    }

    
    Nodo<T>* rotacao_esqdir(Nodo<T>* nodo) {

        nodo->filhoEsquerda = rotacao_esq(nodo->filhoEsquerda);

        return rotacao_dir(nodo);
    }

    
    Nodo<T>* rotacao_diresq(Nodo<T>* nodo) {

        nodo->filhoDireita = rotacao_dir(nodo->filhoDireita);

        return rotacao_esq(nodo);
    }

    
    Nodo<T>* balancear_nodo(Nodo<T>* nodo) { 
        
        
        int balanceamento = valor_balanceamento(nodo);

        
        if (balanceamento > 1 && valor_balanceamento(nodo->filhoEsquerda) >= 0) {
           
            return rotacao_dir(nodo);
        }

        
        if (balanceamento < -1 && valor_balanceamento(nodo->filhoDireita) <= 0) {

            return rotacao_esq(nodo);
        }
        
        
        if (balanceamento < -1 && valor_balanceamento(nodo->filhoDireita) > 0) {

            return rotacao_diresq(nodo);
        }

        
        if (balanceamento > 1 && valor_balanceamento(nodo->filhoEsquerda) < 0) {
            
            return rotacao_esqdir(nodo);
        }

        atualizar_altura(nodo);
        
        return nodo;
    
    }

    Nodo<T>* inserir_nodo(Nodo<T>* nodo, T chave)  {
        
        if (nodo == nullptr) {
           
            return new Nodo<T>{ chave };
        
        }
            
        if (chave > nodo->chave) {

            nodo->filhoDireita = inserir_nodo(nodo->filhoDireita, chave);
        }
        
        else if (chave < nodo->chave) {
            
            nodo->filhoEsquerda = inserir_nodo(nodo->filhoEsquerda, chave);
        
        }
        
       else {
            
            return nodo;
        }

        return balancear_nodo(nodo);
    }

    Nodo<T>* achar_minimo(Nodo<T>* nodo) const {
        
        while (nodo->filhoEsquerda != nullptr) 
        {
            nodo = nodo->filhoEsquerda;
        }
        return nodo;
    }

    Nodo<T>* remocao_nodo(Nodo<T>* nodo, T chave) {
        
        if (nodo == nullptr) {
            
            return 0; 
        }

        if (chave > nodo->chave) {
            
            nodo->filhoDireita = remocao_nodo(nodo->filhoDireita, chave);
        }
        
        else if (chave < nodo->chave) {
            
            nodo->filhoEsquerda = remocao_nodo(nodo->filhoEsquerda, chave);
        }
        
        else {
            
            if (nodo->filhoEsquerda == nullptr || nodo->filhoDireita == nullptr) {
                
                Nodo<T>* aux;
                
                if (nodo->filhoEsquerda != nullptr) {
                    
                    aux = nodo->filhoEsquerda;
                }
                
                else {
                    
                    aux = nodo->filhoDireita;
                }

                if (aux == nullptr) {
                    
                    aux = nodo;
                    
                    nodo = nullptr;
                }
                
                else {
                    
                    *nodo = *aux; 
                }

                delete aux;
            }
            else {
                
                Nodo<T>* aux = achar_minimo(nodo->filhoDireita); 
                
                nodo->chave = aux->chave; 
                
                nodo->filhoDireita = remocao_nodo(nodo->filhoDireita, aux->chave); 
            }
        }

        if (nodo == nullptr) {
            
            return 0;
        }

        
        return balancear_nodo(nodo); 
    }



    void recursivo_preO(ListaEncadeadaAbstrata<T>* listaencad, Nodo<T>* nodo) const {

        if (nodo != nullptr)
        {
            listaencad->inserirNoFim(nodo->chave);
            
            recursivo_preO(listaencad, nodo->filhoEsquerda);
            
            recursivo_preO(listaencad, nodo->filhoDireita);
        }
        
    }

    void recursivo_emO(ListaEncadeadaAbstrata<T>* listaencad, Nodo<T>* nodo) const {

        if (nodo!= nullptr)
        {
            recursivo_emO(listaencad, nodo->filhoEsquerda);
            
            listaencad->inserirNoFim(nodo->chave);
            
            recursivo_emO(listaencad, nodo->filhoDireita);
        }

    }
    void recursivo_posO(ListaEncadeadaAbstrata<T>* listaencad, Nodo<T>* nodo) const {
    
        if (nodo != nullptr)
        {
            recursivo_posO(listaencad, nodo->filhoEsquerda);
            
            recursivo_posO(listaencad, nodo->filhoDireita);
            
            listaencad->inserirNoFim(nodo->chave);
        }
    }

public:
    MinhaArvoreAVL() : ArvoreBinariaDeBusca<T>() {}
    
    virtual ~MinhaArvoreAVL() {
        
        destrutor_arvore(this->raiz);
    
    }
    
    /**
     * @brief Verifica se a arvore esta vazia
     * @return Verdade se a arvore esta vazia.
    */
    virtual bool vazia() const {
        
        if (this->raiz == nullptr) {
        
            return true;
        }
        
        else {
        
            return false;
        }
    }
    
    /**
     * @brief Retornar quantidade de chaves na arvore
     * @return Numero natural que representa a quantidade de chaves na arvore
     */
    virtual int quantidade() const {
        
        return aux_quant(this->raiz);
    
    }

    /**
     * @brief Verifica se a arvore contem uma chave
     * @param chave chave a ser procurada na arvore
     * @return Verdade se a arvore contem a chave
     */
    virtual bool contem(T chave) const {
        
        Nodo<T>* nodo;
        
        nodo = achar_nodo(this->raiz, chave);


        if (nodo != nullptr) {
            
            return true;
        
        }
        
        else {
           
            return false;
            
        }

       
    
    }

    /**
     * @brief Retorna a altura da (sub)arvore
     * @param chave chave que é raiz da (sub)arvore cuja altura queremos.
     * @return Numero inteiro representando a altura da (subarvore). Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<int> altura(T chave) const {
       
        Nodo<T>* nodo;
        
        nodo = achar_nodo(this->raiz, chave);
        
        if (nodo == nullptr) 
        {
            return std::nullopt;
        
        }
        else {
            return valor_altura(nodo);
        }
    }

    /**
     * @brief Insere uma chave na arvore
     * @param chave chave a ser inserida
     */
    virtual void inserir(T chave) {
        
        this->raiz = inserir_nodo(this->raiz, chave);
    
    }

    /**
     * @brief Remove uma chave da arvore
     * @param chave chave a removida
     */
    virtual void remover(T chave) {
        
        this->raiz = remocao_nodo(this->raiz, chave);
    
    }

    /**
     * @brief Busca a chave do filho a esquerda de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a esquerda
     * @return Chave do filho a esquerda. Se chave nao esta na arvore, retorna std::nullopt
     */
    virtual std::optional<T> filhoEsquerdaDe(T chave) const {
       
        Nodo<T>* nodo;
        
        nodo = achar_nodo(this->raiz, chave);
        
        if (nodo != nullptr && nodo->filhoEsquerda != nullptr) {
            
            return nodo->filhoEsquerda->chave;
        
        }
        
        else {
            
            return std::nullopt;
        
        }   
    }

    
    /**
     * @brief Busca a chave do filho a direita de uma (sub)arvore
     * @param chave chave da arvore que eh pai do filho a direita
     * @return Chave do filho a direita. Se chave nao esta na arvore, retorna nullptr
     */
    virtual std::optional<T> filhoDireitaDe(T chave) const {
        
        Nodo<T>* nodo;
        
        nodo = achar_nodo(this->raiz, chave);
        
        if (nodo != nullptr && nodo->filhoDireita != nullptr) {
            
            return nodo->filhoDireita->chave;
        
        }
        
        else {
            
            return std::nullopt;
        
        }
    
    }

    
    /**
     * @brief Lista chaves visitando a arvore em ordem
     * @return Lista encadeada contendo as chaves em ordem.
     */
    virtual ListaEncadeadaAbstrata<T>* emOrdem() const {
        
        ListaEncadeadaAbstrata<T>* lista_emO = new MinhaListaEncadeada<T>;

        recursivo_emO(lista_emO, this->raiz);

        return lista_emO;
    }

    /**
     * @brief Lista chaves visitando a arvore em pre-ordem
     * @return Lista encadeada contendo as chaves em pre-ordem.
     */
    virtual ListaEncadeadaAbstrata<T>* preOrdem() const {
       
        ListaEncadeadaAbstrata<T>* lista_preO = new MinhaListaEncadeada<T>;
        
        recursivo_preO(lista_preO, this->raiz);

        return lista_preO;
    }

    /**
     * @brief Lista chaves visitando a arvore em pos-ordem
     * @return Lista encadeada contendo as chaves em pos ordem.
     */
    virtual ListaEncadeadaAbstrata<T>* posOrdem() const {

        ListaEncadeadaAbstrata<T>* lista_posO = new MinhaListaEncadeada<T>;
       
        recursivo_posO(lista_posO, this->raiz);

        return lista_posO;
    
    }
};

#endif 
