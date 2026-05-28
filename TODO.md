# Rick Dangerous 1 - Lista de Tarefas do Clone SDL3

## Milestone 1: O Nascimento do Motor (Base Técnica)
- [x] **Motor (Engine)**: Criar o Singleton para gerir o ciclo de vida da aplicação (Init, Loop, Clean).
- [x] **Janela (WindowManager)**: Abstração para criar a janela e o renderer no SDL3.
- [x] **InputHandler**: Centralizar a gestão do teclado (Milestone 1 & 2 iniciadas).
- [x] **Recursos (ResourceManager)**: Sistema básico (Singleton) para gerir texturas e evitar duplicados.

## Milestone 2: O Primeiro Sprite e Movimento
- [x] **Sprites**: Classe para renderizar uma imagem ou parte de um spritesheet.
- [x] **Entidade (Entity)**: Classe base com posição e propriedades físicas básicas.
- [x] **Jogador (Rick)**: Implementar a lógica de movimento horizontal e salto (sem animação complexa).
- [x] **InputHandler**: Centralizado e integrado no Player para movimento.

## Milestone 3: O Mundo e as Colisões
- [ ] **Mapa (TileMap)**: Carregar uma matriz simples de tiles e renderizar no ecrã.
- [ ] **Mapa (TileMap) - MVP**: Definir tamanho do tile (ex: 32x32), largura/altura do mapa e matriz 2D de inteiros.
- [ ] **Mapa (TileMap) - Dados**: Criar um loader inicial (hardcoded ou ficheiro .txt) para popular a matriz.
- [ ] **Mapa (TileMap) - Render**: Desenhar tiles sólidos e vazios com cores/sprites para validar visualmente.
- [ ] **Câmara**: Seguir o Rick conforme ele se move pelo mapa.
- [ ] **Câmara - Limites**: Impedir a câmara de mostrar fora dos limites do mapa.
- [ ] **Física (Collisions)**: Implementar detecção AABB para o Rick não atravessar o chão ou paredes.
- [x] **Física (Atual)**: Chão temporário por limite inferior do ecrã já funcional no Player.
- [ ] **Física (Collisions) - MVP**: Separar colisão horizontal e vertical contra tiles sólidos.
- [ ] **Física (Collisions) - Estado**: Atualizar corretamente flag onGround após resolução de colisão.
- [ ] **Animações**: Classe para gerir sequências de frames (Idle, Walk, Jump).
- [ ] **Animações - MVP**: Implementar Animation com frameCount, frameDuration e loop.
- [ ] **Animações - Integração**: Trocar animação do Rick por estado (Idle/Walk/Jump).

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
