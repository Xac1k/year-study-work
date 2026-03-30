"""
Интерактивный просмотр воксельной сетки БПЛА
=============================================
Зависимости:
    pip install matplotlib numpy

Управление:
    - Левая кнопка мыши + перетаскивание  →  вращение
    - Правая кнопка мыши + перетаскивание  →  масштаб
    - Средняя кнопка мыши + перетаскивание →  панорамирование
    - Колесо мыши                           →  масштаб
"""

import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D          # noqa: F401
from mpl_toolkits.mplot3d.art3d import Line3DCollection


# ── Параметры сетки ────────────────────────────────────────────────────────
NX, NY, NZ = 3, 3, 3          # количество точек по каждой оси
SPACING_XZ = 100.0               # шаг между точками по X и Z (горизонталь)
SPACING_Y  = 100.0               # шаг между слоями по Y (глубина)

# ── Цвета и размеры ────────────────────────────────────────────────────────
POINT_COLOR  = '#22aa44'
POINT_SIZE   = 30              # pt²
EDGE_COLOR   = 'black'
EDGE_WIDTH   = 0.9

# ── Начальный угол обзора (истинные 45° к каждой оси) ─────────────────────
ELEV_INIT = 35.264             # arctan(1/√2) ≈ 35.26°
AZIM_INIT = 45.0


def build_grid(nx, ny, nz, sx, sy, sz):
    """Возвращает массив всех узловых точек сетки."""
    pts = []
    for i in range(nx):
        for j in range(ny):
            for k in range(nz):
                pts.append([i * sx, j * sy, k * sz])
    return np.array(pts)


def build_edges(nx, ny, nz, sx, sy, sz):
    """
    Возвращает все рёбра внутренней сетки —
    соединяет каждую точку с соседней по X, Y и Z.
    """
    edges = []
    for i in range(nx):
        for j in range(ny):
            for k in range(nz):
                x = i * sx
                y = j * sy
                z = k * sz
                # ребро по X
                if i + 1 < nx:
                    edges.append([(x, y, z), ((i+1)*sx, y, z)])
                # ребро по Y
                if j + 1 < ny:
                    edges.append([(x, y, z), (x, (j+1)*sy, z)])
                # ребро по Z
                if k + 1 < nz:
                    edges.append([(x, y, z), (x, y, (k+1)*sz)])
    return edges


def main():
    pts   = build_grid(NX, NY, NZ, SPACING_XZ, SPACING_Y, SPACING_XZ)
    edges = build_edges(NX, NY, NZ, SPACING_XZ, SPACING_Y, SPACING_XZ)

    fig = plt.figure(figsize=(8, 8))
    fig.patch.set_facecolor('white')
    ax = fig.add_subplot(111, projection='3d')
    ax.set_facecolor('white')

    # ── Рёбра куба ────────────────────────────────────────────────────────
    lc = Line3DCollection(edges, colors=EDGE_COLOR, linewidths=EDGE_WIDTH, zorder=1)
    ax.add_collection3d(lc)

    # ── Точки ─────────────────────────────────────────────────────────────
    ax.scatter(
        pts[:, 0], pts[:, 1], pts[:, 2],
        color=POINT_COLOR,
        s=POINT_SIZE,
        depthshade=False,
        linewidths=0,
        zorder=1,
    )

    # ── Пропорции и пределы ───────────────────────────────────────────────
    pad = 0.4
    ax.set_xlim(-pad, (NX - 1) * SPACING_XZ + pad)
    ax.set_ylim(-pad, (NY - 1) * SPACING_Y  + pad)
    ax.set_zlim(-pad, (NZ - 1) * SPACING_XZ + pad)

    # Сохраняем истинные пропорции: длина по Y вдвое больше X и Z
    ax.set_box_aspect([(NX - 1) * SPACING_XZ,
                       (NY - 1) * SPACING_Y,
                       (NZ - 1) * SPACING_XZ])

    # ── Начальный угол обзора ─────────────────────────────────────────────
    ax.view_init(elev=ELEV_INIT, azim=AZIM_INIT)

    # ── Убираем оси и фоновые панели ──────────────────────────────────────
    ax.axis('off')
    ax.grid(False)
    for pane in (ax.xaxis.pane, ax.yaxis.pane, ax.zaxis.pane):
        pane.fill = False
        pane.set_edgecolor('none')

    fig.tight_layout(pad=0.5)
    plt.show()


if __name__ == '__main__':
    main()