# Compacta/Descompacta

[github](https://github.com/fmbarina/data-structures-prj2) | [docs](https://fmbarina.github.io/data-structures-prj2)

O projeto possui dois programas: compacta e descompacta. Por meio do algoritmo de codificação Huffman, esses devem, respectivamente, compactar e descompactar arquivos diversos como texto, imagens, audio, etc. Os componentes (TADs e bibliotecas) utilizados em sua na concepção estão [documentados online](https://fmbarina.github.io/data-structures-prj2), graças ao uso do [Doxygen](https://www.doxygen.nl) e [doxygen-awesome-css](https://jothepro.github.io/doxygen-awesome-css/).

# Como usar

Para compilar, rode `make`.

Com o `compacta.out` e `descompacta.out`, basta rodar:

- `./compacta.out <arquivo normal>` para compactar um arquivo.
- `./descompacta.out <arquivo compactado>` para descompactar um arquivo compactado.

Note que os arquivos compactados tem sua extensão substituida por `.comp`, mas ao descompactar a extensão original retornará. 

O repositório também inclui um script de teste automático e alguns arquivos de amostra. Ele compacta, descompacta e compara o arquivo resultante com o original, informando se são idênticos ou se há diferenças, em qual caso houveram falhas no processo.

- Para realizar testes automaticos, rode o script com `./runtests.sh`.
- Para adicionar testes, crie uma nova pasta dentro de `tests/` e coloque o arquivo que deseja compactar dentro.

# Créditos

Veja atribuições em [LICENSE](https://github.com/fmbarina/data-structures-prj2/blob/gh-pages/LICENSE).