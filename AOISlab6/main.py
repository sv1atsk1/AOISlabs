from hash_table import Hash_Table

KEYS = [
        "Ketamine", "Lorazepam", "Dexamethasone", "Furosemide", "Epinephrine",
        "Ondansetron", "Metoprolol", "Ceftriaxone", "Dobutamine", "Levothyroxine",
        "Ranitidine", "Amiodarone", "Morphine", "Lidocaine", "Atropine",
        "Midazolam", "Diazepam", "Phenylephrine", "Epinephrine", "Nitroglycerin",
        "Hydromorphone", "Codeine", "Tramadol", "Oxycodone", "Acetaminophen",
        "Ibuprofen", "Naproxen", "Aspirin", "Fentanyl", "Methadone",
        "Ketorolac", "Diphenhydramine", "Loratadine", "Fexofenadine", "Cetirizine",
        "Hydroxyzine", "Montelukast", "Albuterol", "Ipratropium", "Tiotropium",
        "Beclomethasone", "Budesonide", "Fluticasone", "Prednisone", "Methylprednisolone",
        "Levodopa", "Carbidopa", "Ropinirole", "Pramipexole", "Selegiline",
        "Entacapone", "Bupropion", "Mirtazapine", "Escitalopram", "Sertraline"
]

VALUES = [
        "Magnesium sulfate", "Oxytocin", "Misoprostol", "Erythromycin", "Azithromycin",
        "Clindamycin", "Metronidazole", "Doxycycline", "Amoxicillin", "Cephalexin",
        "Cefazolin", "Vancomycin", "Meropenem", "Cefepime", "Linezolid",
        "Clotrimazole", "Terbinafine", "Fluconazole", "Nystatin", "Acyclovir",
        "Valacyclovir", "Oseltamivir", "Ribavirin", "Sofosbuvir", "Ledipasvir",
        "Immunoglobulin", "Tetanus toxoid", "Diphtheria toxoid", "Pertussis vaccine", "Influenza vaccine",
        "Hepatitis A vaccine", "Hepatitis B vaccine", "Human papillomavirus vaccine", "Meningococcal vaccine", "Pneumococcal vaccine",
        "Varicella vaccine", "Measles vaccine", "Mumps vaccine", "Rubella vaccine", "Yellow fever vaccine",
        "Rabies vaccine", "Typhoid vaccine", "Cholera vaccine", "Bacillus Calmette-Guérin vaccine", "Tuberculin skin test",
        "Colonoscopy", "Endoscopy", "Biopsy", "Mammography", "Pap smear",
        "X-ray", "CT scan", "MRI", "Ultrasound", "Electrocardiogram"
]

def main():
    hash_table = Hash_Table()
    for i in range(51):
        hash_table.add_hash_line([KEYS[i], VALUES[i]])
    hash_table.print_table()
    print("--------------------------------------------------------------------------------------------------------------------------------------------------------------")
        
    hash_table.delete_element('Fexofenadine')
    hash_table.delete_element('Nitroglycerin')

    hash_table.print_new_table()

    hash_table.search_for_element('Ondansetron')
    hash_table.search_for_element('Selegiline')

if __name__ == '__main__':
    main()