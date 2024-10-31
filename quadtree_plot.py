import matplotlib.pyplot as plt
import re

def parse_quadtree_file(filename):

    node_data = []
    points = []

    with open(filename, 'r', encoding='utf-8') as file:

        for line in file:

            line = line.strip()
            level = line.count('--')
            line_content = line.replace('--', '').strip()

            # cuadrantes lineas
            if line_content.startswith("Cuadrante"):

                cuadrante_match = re.search(r"Cuadrante \((\d+), (\d+)\), Ancho: (\d+), Altura: (\d+)", line_content)
                
                if cuadrante_match:
                    x = int(cuadrante_match.group(1))
                    y = int(cuadrante_match.group(2))
                    width = int(cuadrante_match.group(3))
                    height = int(cuadrante_match.group(4))
                    node_data.append({"x": x, "y": y, "width": width, "height": height, "level": level})

                else:
                    print(f"Error al procesar la línea de cuadrante: '{line_content}'.")

            # puntos 
            elif line_content.startswith("Punto"):
                punto_match = re.search(r"Punto \((\d+), (\d+)\)", line_content)
                if punto_match:
                    x = int(punto_match.group(1))
                    y = int(punto_match.group(2))
                    points.append((x, y))
                else:
                    print(f"Error al procesar la línea de punto: '{line_content}'.")

    return node_data, points

def plot_quadtree(node_data, points):

    fig, ax = plt.subplots()

    for node in node_data:

        x = node["x"] - node["width"] / 2
        y = node["y"] - node["height"] / 2

        width = node["width"]
        height = node["height"]
        edge_color = 'blue' if node["level"] % 2 == 0 else 'green'
        rect = plt.Rectangle((x, y), width, height, fill=False, edgecolor=edge_color, linestyle='--', linewidth=0.8)

        ax.add_patch(rect)

    xs, ys = zip(*points) if points else ([], [])
    plt.scatter(xs, ys, color='red', marker='o', s=10, label="Puntos")

    ax.set_aspect('equal')
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("Visualización del QuadTree")
    plt.grid(True)
    plt.show()

if __name__ == "__main__":

    node_data, points = parse_quadtree_file("quadtree_structure.txt")
    plot_quadtree(node_data, points)
