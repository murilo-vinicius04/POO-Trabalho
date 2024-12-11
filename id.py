# Caminho do arquivo original e o de saída
input_file_path = '/home/murilo/POO/TRABALHO/perguntas.txt'
output_file_path = '/home/murilo/POO/TRABALHO/perguntas_id.txt'

# Lê o arquivo original e adiciona IDs únicos no início de cada linha
with open(input_file_path, 'r') as infile, open(output_file_path, 'w') as outfile:
    for idx, line in enumerate(infile, start=1):
        outfile.write(f"{idx};{line}")

print(f"Arquivo com IDs gerado: {output_file_path}")
