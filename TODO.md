# Rick Dangerous 1 - Lista de Tarefas do Clone SDL3

## Milestone 1: O Nascimento do Motor (Base Técnica)
- [x] **Motor (Engine)**: Criar o Singleton para gerir o ciclo de vida da aplicação (Init, Loop, Clean).
- [x] **Janela (WindowManager)**: Abstração para criar a janela e o renderer no SDL3.
- [x] **Input Básico**: Capturar eventos de fechar janela e teclas essenciais (ESC).
- [ ] **Recursos (ResourceManager)**: Sistema básico (Singleton/Template) para carregar e armazenar texturas.

## Milestone 2: O Primeiro Sprite e Movimento
- [ ] **Sprites**: Classe para renderizar uma imagem ou parte de um spritesheet.
- [ ] **Entidade (Entity)**: Classe base com posição e propriedades físicas básicas.
- [ ] **Jogador (Rick)**: Implementar a lógica de movimento horizontal e salto (sem animação complexa).
- [ ] **InputHandler**: Mapeamento de teclas para ações do jogo (Esquerda, Direita, Salto).

## Milestone 3: O Mundo e as Colisões
- [ ] **Mapa (TileMap)**: Carregar uma matriz simples de tiles e renderizar no ecrã.
- [ ] **Câmara**: Seguir o Rick conforme ele se move pelo mapa.
- [ ] **Física (Collisions)**: Implementar detecção AABB para o Rick não atravessar o chão ou paredes.
- [ ] **Animações**: Classe para gerir sequências de frames (Idle, Walk, Jump).

## Milestone 4: Combate e Perigos
- [ ] **Armas**: Implementar a lógica do bastão (melee), pistola e dinamite.
- [ ] **Armadilhas (Hazards)**: Pedras que rolam, espinhos e dardos.
- [ ] **Inimigos**: IA básica de patrulha e morte.

## Milestone 5: Sistemas de Jogo e Interface
- [ ] **HUD**: Mostrar vidas, munição e pontuação no ecrã.
- [ ] **Áudio (AudioManager)**: Implementar sons de saltos, tiros e música de fundo.
- [ ] **Menus**: Ecrã de título, seleção de nível e Game Over.
- [ ] **Transições**: Lógica para mudar de nível ou reiniciar ao morrer.

## Milestone 6: Polimento e Conteúdo
- [ ] Implementar níveis completos do jogo original.
- [ ] Ajustar tempos (Timings) e dificuldades.
- [ ] Suporte para Gamepad total.

## Arquitetura de Classes Sugerida:
```cpp
// Estrutura de pastas pretendida:
// src/core/      -> Engine, WindowManager, InputHandler
// src/graphics/  -> Sprite, Animation, Camera, Texture
// src/entities/  -> Entity, Player, Enemy, Hazard
// src/world/     -> TileMap, CollisionSystem
// src/utils/     -> ResourceManager, Logger, Math
// src/audio/     -> AudioManager
```
