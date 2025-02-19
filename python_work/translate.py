import pandas as pd
import nltk
from nltk.corpus import wordnet
import hashlib
import requests
import time

# 下载NLTK数据（第一次运行需要）
# nltk.download('punkt')
# nltk.download('averaged_perceptron_tagger')
# nltk.download('wordnet')

# 百度翻译API配置
BAIDU_APPID = '20250219002278333'  # 替换为你的百度翻译APPID
BAIDU_APPKEY = 'GcElOZ_hUKMObI_jL8TJ'  # 替换为你的百度翻译APPKEY
BAIDU_API_URL = "https://fanyi-api.baidu.com/api/trans/vip/translate"

def get_simple_pos(tag):
    """将NLTK词性标签转换为简写形式"""
    if tag.startswith('J'):
        return '.adj'  # 形容词
    elif tag.startswith('V'):
        return '.v'    # 动词
    elif tag.startswith('N'):
        return '.n'    # 名词
    elif tag.startswith('R'):
        return '.adv'  # 副词
    elif tag == 'MD':
        return '.modal'  # 情态动词
    elif tag.startswith('IN'):
        return '.prep'  # 介词或从属连词
    elif tag == 'CC':
        return '.conj'  # 连词
    elif tag == 'DT':
        return '.det'   # 限定词
    elif tag == 'PRP' or tag == 'PRP$':
        return '.pron'  # 代词
    elif tag == 'UH':
        return '.interj'  # 感叹词
    elif tag.startswith('CD'):
        return '.num'   # 数词
    else:
        return 'what the hell is this?'

def baidu_translate(word, appid, appkey):
    """调用百度翻译API进行翻译"""
    salt = '12345'  # 随机字符串
    sign = hashlib.md5((appid + word + salt + appkey).encode()).hexdigest()
    
    params = {
        'q': word,
        'from': 'en',
        'to': 'zh',
        'appid': appid,
        'salt': salt,
        'sign': sign
    }
    
    try:
        response = requests.get(BAIDU_API_URL, params=params)
        result = response.json()
        if 'trans_result' in result:
            return result['trans_result'][0]['dst']  # 返回翻译结果
        else:
            print(f"翻译失败：{result}")
            return "翻译失败"
    except Exception as e:
        print(f"请求百度翻译API出错：{e}")
        return "翻译失败"

def process_excel(input_path, output_path):
    """处理Excel文件"""
    # 读取Excel文件
    df = pd.read_excel(input_path, engine='openpyxl')
    
    # 处理每个单词
    for index, row in df.iterrows():
        word = str(row[1]).strip()  # 假设第二列是B列（索引1）
        if word[-1] == '*':
            word = word[:-1]
        
        # 获取词性
        pos_tag = nltk.pos_tag([word])[0][1]
        df.at[index, '词性'] = get_simple_pos(pos_tag)
        # df.at[index, '词性'] = pos_tag
        
        # 获取中文翻译
        translation = baidu_translate(word, BAIDU_APPID, BAIDU_APPKEY)
        df.at[index, '中文'] = translation

        time.sleep(1)
    # 保存结果
    df.to_excel(output_path, index=False, engine='openpyxl')
    print(f"处理完成！结果已保存至 {output_path}")

# 使用示例
if __name__ == "__main__":
    input_file = r"C:\Users\admin\Desktop\input_e.xlsx"  # 输入文件路径
    output_file = r"C:\Users\admin\Desktop\output.xlsx"  # 输出文件路径
    process_excel(input_file, output_file)