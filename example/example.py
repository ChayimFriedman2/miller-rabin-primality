from miller_rabin_primarility import is_prime


def at(iterable, index):
    iterator = iter(iterable)
    try:
        for i in range(index + 1):
            result = next(iterator)
    except StopIteration:
        return None
    else:
        return result

def primes_gen():
    num = 2
    while True:
        if is_prime(num):
            yield num
        num += 1

if '__main__' == __name__:
    index = int(input('Find the nth prime: '))
    if index < 1:
        raise ValueError()
    elif 1 == index:
        index_text = '1st'
    elif 2 == index:
        index_text = '2nd'
    elif 3 == index:
        index_text = '3rd'
    else:
        index_text = str(index) + 'th'
    print('The', index_text, 'prime is', at(primes_gen(), index - 1), sep=' ')
